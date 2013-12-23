// Timeout for (any) http requests, in milliseconds
var g_xhr_timeout = 10000;

/**
 * XHR wrapper
 * Usage:
 * ask({
 *   url: ...,
 *   method: null, // default depends on data: GET or POST
 *   data: null, // null => default GET
 *   headers: additional request headers (eg: {'Content-Type': 'text/plain'}
 *   success: function(text, event, xhr){...},
 *   failure: function(code, text, event, xhr){...},
 * });
 */
function ask(o) {
	function p(name, def) {
		return o[name] || def;
	}
	var req = new XMLHttpRequest();
	req.open(p('method', (o.data?'POST':'GET')), o.url, true); // open async
	headers = p('headers', {});
	for(h in headers)
		req.setRequestHeader(h, headers[h]);
	req.onload = function(e) {
		if(req.readyState == 4) {
			clearTimeout(xhrTimeout); // got response, no more need in timeout
			text = req.responseText;
			if(req.status == 200) {
				console.log("xhr:success");
				if(o.success)
					o.success(text, e, req);
			} else {
				console.log("xhr:error "+req.status+"\n"+text);
				if(o.failure)
					o.failure(req.status, text, e, req);
			}
		}
	};
	req.send(p('data', null));
	var xhrTimeout = setTimeout(function() {
		req.abort();
		displayError("Request timed out");
	}, g_xhr_timeout);
}
/**
 * Usage:
 * getJson(url, success_func, failure_func)
 * or
 * getJson(url, success_func, true) to use the same function
 *
 * success(data, event, xhr)
 * failure(err_code, data, event, xhf)
 */
function getJson(url, success, failure, headers, method, data) {
	ask({
			url: url,
			headers: headers,
			method: method,
			data: data,
			success: function(text, e, xhr) {
				if(success)
					success(JSON.parse(text), e, xhr);
			},
			failure: function(code, text, e, xhr) {
				if(failure === true) {
					if(success)
						success(JSON.parse(text), e, xhr);
				} else if(failure) // function
					failure(code, JSON.parse(text), e, xhr);
			}
	});
}

var g_access_token = "";
var g_refresh_token = "";

/**
 * send query to googleTasks api.
 * Will automatically send error message to Pebble
 * if anything goes wrong.
 *
 * endpoint: e.g. users/@me/lists or lists/.../tasks
 * params: {} with all args
 * success: callback(json)
 * method: get or post or something else (defaults to Get)
 * data: n/a for get method
 */
function queryTasks(endpoint, params, success, method, send_data) {
	var url = "https://www.googleapis.com/tasks/v1/" + endpoint;
	var sep = "?";
	if(params) {
		for(p in params)
			url += sep + encodeURIComponent(p) + "=" + encodeURIComponent(params[p]);
		sep = "&";
	}
	var headers = {"Authorization": "Bearer "+g_access_token};
	getJson(url, success, function(code, data) {
		if(code == 401) { // Invalid Credentials
			console.log("Renewing token and retrying...");
			renewToken(function() { // renew, and on success -
				headers = {"Authorization": "Bearer "+g_access_token}; // the new one
				getJson(url, success, function(code, data) {
					console.log("Renewal didn't help! "+code+": "+data.error.message);
					displayError(data.error.message, code);
				}, headers, method, send_data);
			});
		} else {
			displayError(data.error.message, code);
		}
	}, headers, method, send_data);
}

/**
 * Checks current g_access_token for validity (TODO)
 * and requests new if neccessary,
 * after which calls Success callback.
 * [Now just requests new token and saves it]
 * In case of error it will call displayError.
 */
function renewToken(success) {
	console.log("Renewing token!");
	refresh_token = g_refresh_token;
	if(!refresh_token) {
		displayError("No refresh token; please log in!", 401);
		return;
	}
	getJson("https://pebble-notes.appspot.com/v1/auth/refresh?refresh_token="+encodeURIComponent(refresh_token),
		function(data) { // success
			console.log("Renewed. "+JSON.stringify(data));
			if("access_token" in data) {
				localStorage["access_token"] = data.access_token;
				g_access_token = data.access_token;
				success(g_access_token);
			} else if("error" in data) {
				displayError(data.error);
			} else {
				displayError("No access token received from Google!"); // unlikely...
			}
		},
		function(code, data) { // failure
			displayError(data.error.message, code);
		});
}

/**
 * Sends an error packet to Pebble
 * code may be null
 */
function displayError(text, code) {
	if(code) text += " (" + code + ")";
	console.log("Sending error msg to Pebble: " + text);
	sendMessage({
			code: 50, // Error
			error: text
	});
}
function assert(val, message) {
	if(!val) {
		console.log("assertion failed");
		displayError(message);
	}
}

var g_msg_buffer = [];
var g_msg_transaction = null;

/**
 * Sends appMessage to pebble; logs errors.
 * failure: may be True to use the same callback as for success.
 */
function sendMessage(data, success, failure) {
	function sendNext() {
		g_msg_transaction = null;
		next = g_msg_buffer.shift();
		if(next) { // have another msg to send
			sendMessage(next);
		}
	}
	if(g_msg_transaction) { // busy
		g_msg_buffer.push(data);
	} else { // free
		g_msg_transaction = Pebble.sendAppMessage(data,
			function(e) {
				console.log("Message sent for transactionId=" + e.data.transactionId);
				if(g_msg_transaction != e.data.transactionId)
					console.log("### Confused! Message sent which is not a current message. "+
							"Current="+g_msg_transaction+", sent="+e.data.transactionId);
				if(success)
					success();
				sendNext();
			},
		   	function(e) {
				console.log("Failed to send message for transactionId=" + e.data.transactionId + ", error is "+e.error.message);
				if(g_msg_transaction != e.data.transactionId)
					console.log("### Confused! Message not sent, but it is not a current message. "+
							"Current="+g_msg_transaction+", unsent="+e.data.transactionId);
				if(failure === true) {
					if(success)
						success();
				} else if(failure)
					failure();
				sendNext();
			});
			console.log("transactionId="+g_msg_transaction+" for msg "+JSON.stringify(data));
	}
}
var g_ready = false;
/**
 * Send "ready" msg to watchapp: we are now ready to return data from google
 */
function ready() {
	if(g_ready) // already sent
		return;
	sendMessage({code: 0});
	g_ready = true;
}

var g_tasklists = [];

/**
 * Compare two strings; for array sorting.
 */
function strcmp(a, b) {
	if(a<b) return -1;
	if(a>b) return 1;
	return 0;
}

/* Main logic */
function doGetAllLists() {
	console.log("Querying all tasklists");
	queryTasks("users/@me/lists", null, function(d) {
		console.log("sending " + d.items.length + " items");
		g_tasklists = []; // TODO: use it for caching
		for(var i=0; i<d.items.length; i++) {
			var l = d.items[i];
			g_tasklists.push({
					id: l.id,
					title: l.title,
					size: -1
			});
		}
		g_tasklists.sort(function(a, b) {
			return strcmp(a.title, b.title);
		});
		sendMessage({
				code: 20, // array start/size
				scope: 0,
				count: d.items.length});
		for(i=0; i<g_tasklists.length; i++) {
			console.log("Sending item: " + JSON.stringify(g_tasklists[i]));
			sendMessage({
					code: 21, // array item
					scope: 0,
					item: i,
					listId: i,
					title: g_tasklists[i].title,
					size: g_tasklists[i].size}); // TODO
		}
		sendMessage({
				code: 22, // array end
				scope: 0,
				count: g_tasklists.length}); // send resulting list length, just for any
		console.log("sending finished");
	});
}
function doGetOneList(listId) {
	realId = g_tasklists[listId].id;
	queryTasks("lists/"+realId+"/tasks", null, function(d) {
		// FIXME: support more than 100 tasks (by default Google returns only 100)
		if(d.nextPageToken)
			sendError("There are more tasks than we can process");
		console.log("sending " + d.items.length + " items");
		var tasks = g_tasklists[listId].tasks = []; // TODO: use it for caching
		for(var i=0; i<d.items.length; i++) {
			var l = d.items[i];
			tasks.push({
					id: l.id,
					position: l.position,
					done: l.status == "completed",
					title: l.title,
					hasNotes: "notes" in l,
					notes: l.notes
			});
		}
		tasks.sort(function(a, b) {
			return strcmp(a.position, b.position);
		});
		if(tasks[tasks.length-1].title === "" && !tasks[tasks.length-1].done) // if last task is empty and not completed
			tasks.pop(); // don't show it
		sendMessage({
				code: 20, // array start/size
				scope: 1,
				listId: listId,
				count: tasks.length});
		for(i=0; i<tasks.length; i++) {
			console.log("Sending item: " + JSON.stringify(tasks[i]));
			sendMessage({
					code: 21, // array item
					scope: 1,
					item: i,
					taskId: i,
					isDone: tasks[i].done?1:0,
					title: tasks[i].title,
					hasNotes: tasks[i].hasNotes?1:0,
					notes: tasks[i].notes
			});
		}
		sendMessage({
				code: 22, // array end
				scope: 1,
				listId: listId,
				count: tasks.length}); // send resulting list length, just for any
		console.log("sending finished");
	});
}
function doGetTaskDetails(taskId) {
	assert(false, "Not implemented yet");
}
function doChangeTaskStatus(taskId, isDone) {
	assert(false, "Not implemented yet");
}

/* Initialization */
Pebble.addEventListener("ready", function(e) {
	console.log("JS is running. Okay.");
	g_access_token = localStorage.access_token;
	g_refresh_token = localStorage.refresh_token;
	console.log("access token (from LS): "+g_access_token);
	console.log("refresh token (from LS): "+g_refresh_token.substring(0,5)+"...");

	if(g_refresh_token) // check on refresh token, as we can restore/renew access token later with it
		ready(); // ready: tell watchapp that we are ready to communicate
	else { // try to retrieve it from watchapp
		sendMessage({ code: 41 /* retrieve token */ },
			false, // on success just wait for reply
			function() { // on sending failure tell user to login; although error message is unlikely to pass
				displayError("No refresh token stored, please log in!", 401); // if no code, tell user to log in
			}
		);
	}
});

/* Configuration window */
Pebble.addEventListener("showConfiguration", function(e) {
	console.log("Showing config window... new url");
	Pebble.openURL("http://pebble-notes.appspot.com/v1/notes-config.html?option1=off");
});
Pebble.addEventListener("webviewclosed", function(e) {
	console.log("webview closed: "+e.response);
	result = JSON.parse(e.response);
	if("access_token" in result && "refresh_token" in result) { // assume it was a login session
		console.log("Saving tokens");
		// save tokens
		if(result.access_token) {
			localStorage["access_token"] = g_access_token = result.access_token;
			console.log("Access token: " + g_access_token);
		}
		if(result.refresh_token) {
			localStorage["refresh_token"] = g_refresh_token = result.refresh_token;
			console.log("Refresh token saved: " + g_refresh_token.substring(0,5)+"...");
		}
		// TODO: maybe save expire time for later checks? (now + value)
		// now save tokens in watchapp:
		sendMessage({
				code: 40, // save_token
				access_token: g_access_token,
				refresh_token: g_refresh_token
		});
		ready(); // tell watchapp that we are now ready to work
	}
});

/* Messages */
Pebble.addEventListener("appmessage", function(e) {
	console.log("Received message: " + JSON.stringify(e.payload));
	switch(e.payload.code) {
	case 10: // get info
		switch(e.payload.scope) {
		case 0: // all lists
			doGetAllLists();
			break;
		case 1: // one list
			assert('listId' in e.payload, "List ID was not provided for GetOneList query");
			doGetOneList(e.payload.listId);
			break;
		case 2: // one task
			assert('taskId' in e.payload, "Task ID was not provided for GetTaskDetails query");
			doGetTaskDetails(e.payload.taskId);
			break;
		default:
			console.log("Unknown message scope "+e.payload.scope);
			break;
		}
		break;
	case 11: // change info
		switch(e.payload.scope) {
		case 2: // one task (here - "done" status)
			assert(e.payload.taskId, "Task ID was not provided for ChangeTaskStatus query");
			assert(e.payload.isDone, "New task status was not provided for ChangeTaskStatus query");
			doChangeTaskStatus(e.payload.taskId, e.payload.isDone);
			break;
		case 0: // all lists
		case 1: // one list
			console.log("Cannot 'change' info for scope "+e.payload.scope);
			break;
		default:
			console.log("Unknown message scope "+e.payload.scope);
			break;
		}
		break;
	case 41: // retrieve token - reply received
		g_access_token = e.payload.access_token;
		g_refresh_token = e.payload.refresh_token;
		if(refresh_token) { // it's possible to refresh access token if it was not provided
			console.log("Retrieved tokens from watch: "+g_access_token+", "+g_refresh_token.substring(0,5)+"...");
			// save them (again)
			localStorage.access_token = g_access_token;
			localStorage.refresh_token = g_refresh_token;
			ready(); // ready at last
		} else { // no tokens here nor on watch
			displayError("Please open settings and log in!"); // if no code, tell user to log in
		}
		break;
	default:
		console.log("Unknown message code "+e.payload.code);
		break;
	}
});
