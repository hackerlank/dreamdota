function alert(a,b,c,d){if(a==null)a="";if(!b)b=WScript.ScriptName;if(c==null)c=alert.OKOnly+alert.Exclamation;if(d==null)d=0;return (new ActiveXObject("WScript.Shell")).Popup(a,d,b,c);}(function(a){for(var i in a)alert[i]=a[i];})({Critical:16,Question:32,Exclamation:48,Information:64,OKOnly:0,OKCancel:1,AbortRetryIgnore:2,YesNoCancel:3,YesNo:4,RetryCancel:5,Timeout:-1,OK:1,Cancel:2,Abort:3,Retry:4,Ignore:5,Yes:6,No:7});
//--------------------------------------------------------------------------------

var SRC_PATH = 'Offsets.def';
var OUT_PATH_H = 'Offsets.h';
var OUT_PATH_CPP = 'Offsets.cpp';

var OUT_HEADER = '#include "Offsets.h"\n';
var OUT_MAP_NAME = 'OffsetMap';
var OUT_MAP_SET_FUNC_NAME = 'OffsetSet';

var FSO = new ActiveXObject("Scripting.FileSystemObject");
var SHELLO = new ActiveXObject("Wscript.Shell");

var ForReading = 1, ForWriting = 2, ForAppending = 8;
var TristateUseDefault = -2, TristateTrue = -1, TristateFalse = 0;

var FileContents = null;
var Parsed = null;

function ReplaceMarkContent(name, all, content) {
	var regx = new RegExp('\\/\\*\\<! BEGIN ' + name + ' !\\>\\*\\/[\\s\\S]+\\/\\*\\<! END ' + name + ' !\>\\*\\/', 'gm');
	return all.replace(regx, '\/\*\<! BEGIN ' + name + ' !\>\*\/' + content + '\/\*\<! END ' + name + ' !\>\*\/');
}

function Check() {
	var rv = true;
	if (FSO.FileExists(SRC_PATH)) {
		
	} else {
		alert('File: "' + SRC_PATH + '" does not exist!');
		rv = false;
	}
	return rv;
}

function Read() {
	var ts = FSO.OpenTextFile(SRC_PATH, ForReading, true);
	if (!ts) {
		alert("Read: FSO.OpenTextFile Error!");
		return false;
	}

	FileContents = ts.ReadAll();
	ts.Close();
	return true;
}

function Process() {
	var lines = FileContents.split('\r\n');

	//删除注释清理tab
	for (i = 0; i < lines.length; i++) {
		lines[i] = lines[i].replace(/Offset Table/g, '');
		lines[i] = lines[i].replace(/\/\/.+/g, '');
		lines[i] = lines[i].replace(/^\s+/g, '');
		lines[i] = lines[i].replace(/\s+/g, '|');
	}

	//删除空行
	lines = lines.join('\n').replace(/^\s?\n/g, '').replace(/\n+/g, '\n').split('\n');
	if (!lines[0])
		lines.splice(0, 1);
	if (!lines[lines.length - 1])
		lines.splice(lines.length - 1, 1);

	//读取
	var o = {};
	var versions = lines[0].split('|');
	var offsets = [];
	var t;
	var elements;

	//TODO 检查语法

	for (i = 1; i < lines.length; i++) {
		elements = lines[i].split('|');
		t = elements[0];
		if (t) {
			offsets.push(t);
			o[t] = {};
			for (j = 0; j < versions.length; j++) {
				o[t][versions[j]] = elements[1 + j];
			}
		}
	}

	Parsed = o;

	return true;
}

function Save() {
	var ts = FSO.OpenTextFile(OUT_PATH_H, ForReading, false);
	if (!ts) {
		alert("Save: FSO.OpenTextFile For Reading Error!\nFile: " + OUT_PATH_H);
		return false;
	}
	
	var content = ts.ReadAll();
	ts.Close();

	var o = '\r\n';
	var i = 0;
	for (offset in Parsed) {
		o += '#define ' + offset + ' ' + (++i).toString() + '\r\n';
	}

	out = ReplaceMarkContent('Offset', content, o);

	ts = FSO.OpenTextFile(OUT_PATH_H, ForWriting, true);
	if (!ts) {
		alert("Save: FSO.OpenTextFile For Writing Error!\nFile: " + OUT_PATH_H);
		return false;
	}
	
	ts.Write(out);
	ts.Close();

	ts = FSO.OpenTextFile(OUT_PATH_CPP, ForReading, false);
	if (!ts) {
		alert("Save: FSO.OpenTextFile For Reading Error!\nFile: " + OUT_PATH_CPP);
		return false;
	}
	
	var content = ts.ReadAll();
	ts.Close();
	
	o = '\r\n';

	for (offset in Parsed) {
		o += '//' + offset;
		o += '\r\n';
		
		for (version in Parsed[offset]) {
			//o += ('\t' + OUT_MAP_NAME + '[' + offset + '][' + version + '] = 0x' + parseInt(Parsed[offset][version]).toString(16).toUpperCase() + ';\r\n');
			o += ('\t' + OUT_MAP_SET_FUNC_NAME + '(' + offset + ', ' + version + ', 0x' + parseInt(Parsed[offset][version]).toString(16).toUpperCase() + ');\r\n');
			
		}

		o += ('\r\n\r\n');
	}

	out = ReplaceMarkContent('InitMap', content, o);

	ts = FSO.OpenTextFile(OUT_PATH_CPP, ForWriting, true);
	if (!ts) {
		alert("Save: FSO.OpenTextFile For Writing Error!\nFile: " + OUT_PATH_CPP);
		return false;
	}
	
	ts.Write(out);
	ts.Close();
	return true;
}

if (!(Check() && Read() && Process() && Save())) {
	alert('自动生成偏移代码失败！');
	throw '自动生成偏移代码失败！';
}