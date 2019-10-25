/**
 * @overview
 *
 * @author 
 * @version 2019/08/02
 */

const addon = require('./build/Release/addon');

addon.init('1101181211084462#yuanyin');

const isLoginOk = addon.login("youke123", "youke123", (msg, from, to, type) => {
	console.log('recive:' + msg + 'from:' + from + 'to:' + to + 'type:' + type)
}, msg=>console.error(msg));

const roomId = "96379921825794";

console.log('isLoginOk:', isLoginOk);

setTimeout(() => {
   console.log('joinOk: ', addon.joinChatRoom(roomId));
}, 2000);

setTimeout(() => {
console.log('roomOk: ', addon.joinedChatRoomById(roomId));
},10000);


setTimeout(() => {
console.log('leaveOk: ', addon.leaveChatRoom(roomId));
}, 15000);

setTimeout(() => {
console.log('joinOk: ', addon.joinChatRoom(roomId));
}, 20000);

const express = require('express');
const app = express();
const http = require('http').Server(app);
http.listen(8080, function(){

});

