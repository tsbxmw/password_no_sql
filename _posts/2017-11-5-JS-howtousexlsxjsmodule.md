---
layout: post
title: How use xlsx and bootstrap-table to import xlsx file 
categories: JS
description: bookmark
keywords: javascript, xlsx, bootstrap-table, sheetjs, tableexport
---

How use xlsx and bootstrap-table to import xlsx file & export to a xlsx file

# about

## sheetjs

* official website : http://sheetjs.com/

* github page : https://github.com/sheetjs/js-xlsx

## bootstrap-table

* official websit : http://bootstrap-table.wenzhixin.net.cn/
* github page : https://github.com/wenzhixin/bootstrap-table


# how to use xlsx.js to import one xlsx file?

## using file input

* download the js file : xlsx.full.min.js & css files

----

* the html code

```html
    <center>
    <input type="file" id="inputsheet" onchange="Sheet(this.files)">
    </center>
```

* the js code

xlsxworker.js
```javascript
    /* xlsx.js (C) 2013-present SheetJS -- http://sheetjs.com */
    importScripts('shim.js');
    importScripts('xlsx.full.min.js');
    postMessage({t:"ready"});

    onmessage = function (evt) {
    var v;
    try {
        v = XLSX.read(evt.data.d, {type: evt.data.b});
    postMessage({t:"xlsx", d:JSON.stringify(v)});
    } catch(e) { postMessage({t:"e",d:e.stack||e}); }
    };

```

using the dofile(e) to 

```javascript
   function Sheet(e) {
	var golobal_table = [];
	var X = XLSX;
	var XW = {
		/* worker message */
		msg: 'xlsx',
		/* worker scripts */
		worker: './assets/js/xlsxworker.js'
	};
	var useworker = typeof Worker !== 'undefined';
	var rABS = typeof FileReader !== "undefined" && (FileReader.prototype||{}).readAsBinaryString;
	var use_worker = typeof Worker !== 'undefined';
	var xw = function xw(data, cb) {
		var worker = new Worker(XW.worker);
		worker.onmessage = function(e) {
			switch(e.data.t) {
				case 'ready': break;
				case 'e': console.error(e.data.d); break;
				case XW.msg: cb(JSON.parse(e.data.d)); break;
			}
		};
		worker.postMessage({d:data,b:rABS?'binary':'array'});
	};
	
	function do_file(files) {
		rABS = true;
		use_worker = true;
		var f = files[0];
		var reader = new FileReader();
		reader.onload = function(e) {
			if(typeof console !== 'undefined') console.log("onload", new Date(), rABS, use_worker);
			var data = e.target.result;
			if(!rABS) data = new Uint8Array(data);
			if(use_worker) xw(data, process_wb);
			else process_wb(X.read(data, {type: rABS ? 'binary' : 'array'}));
		};
		if(rABS) reader.readAsBinaryString(f);
		else reader.readAsArrayBuffer(f);
	};
	

	var global_wb;

	var process_wb = (function() {
		var get_format = (function() {
			var radios = document.getElementsByName( "format" );
			return function() {
				for(var i = 0; i < radios.length; ++i) if(radios[i].checked || radios.length === 1) return radios[i].value;
			};
		})();
		var to_json = function to_json(workbook) {
			if(useworker && workbook.SSF) XLSX.SSF.load_table(workbook.SSF);
			var result = {};
			workbook.SheetNames.forEach(function(sheetName) {
				var roa = XLSX.utils.sheet_to_json(workbook.Sheets[sheetName], {header:1});
				if(roa.length > 0) result[sheetName] = roa;
			});
			return result["Sheet1"];
		};

		var to_csv = function to_csv(workbook) {
			var result = [];
			workbook.SheetNames.forEach(function(sheetName) {
				var csv = X.utils.sheet_to_csv(workbook.Sheets[sheetName]);
				if(csv.length){
					result.push("SHEET: " + sheetName);
					result.push("");
					result.push(csv);
				}
			});
			return result.join("\n");
		};

		var to_fmla = function to_fmla(workbook) {
			var result = [];
			workbook.SheetNames.forEach(function(sheetName) {
				var formulae = X.utils.get_formulae(workbook.Sheets[sheetName]);
				if(formulae.length){
					result.push("SHEET: " + sheetName);
					result.push("");
					result.push(formulae.join("\n"));
				}
			});
			return result.join("\n");
		};

		var to_html = function to_html(workbook) {
			HTMLOUT.innerHTML = "";
			workbook.SheetNames.forEach(function(sheetName) {
				var htmlstr = X.write(workbook, {sheet:sheetName, type:'binary', bookType:'html'});
				HTMLOUT.innerHTML += htmlstr;
			});
			return "";
		};

		return function process_wb(wb) {
			global_wb = wb;
			var output = "";
			switch(get_format()) {
				case "form": output = to_fmla(wb); break;
				case "html": output = to_html(wb); break;
				case "json": output = to_json(wb); break;
				default: output = to_json(wb);
			}
			if(typeof console !== 'undefined') console.log("output", output);
			deal(output);
		};
	})();
	

	do_file(e);
};

function deal(json){
    //here to deal the json information
}

```

* now we get the json data in deal.

## using bootstrap to show json info

* download the bootstrap-table.js & css files

----

```html
    <table id="table"  style="font-size:11px;"  data-height="500" data-method="post" data-query-params="queryParams" data-toolbar="#toolbar" 
			data-pagination="true" data-search="false" data-page-size="7">
	        <thead>
	            <tr >
	            	<th class="span3" data-field="index" data-sortable="true">ID</th>
                    <th class="span3" data-field="name" data-sortable="true">NAME</th>
                    <th class="span3" data-field="value" data-sortable="true">VALUE</th>
	            </tr>
	        </thead>
	</table>  

```

```javascript

    function deal(json){
        //here to deal the json data to ID-NAME-VALUE format
        //[{"index":1,"name":"hello","value":499}] 
        //then destroy the table and recreate the table with json data
        $("#table").bootstrapTable('destroy');
        $("#table").bootstrapTable({
            data    : json,
            toolbar : "#toolbar",
            pagination : true,
            pageNumber : 1,
            pageSize : 20,
            pageList : [5,10,20],
            search : true,
            searchAlign : "right",
            exportDataType : "selected",
            cardView : false,
            detailView : false
            });

    
        };
    }
```

## using table export to import as xlsx

* the xlsx demo web url : http://sheetjs.com/demos/table.html

* download and import the tableExport.jquery.plugin file from http://kayalshri.github.io/tableExport.jquery.plugin/

----

```javascript
    //easy to use to export xlsx file.
    function export(){
        $('#table').tableExport({type:'xlsx'},"Bom");
    }

```




> #### LINK

[see the demo at here](https://github.com/tsbxmw/testshow/tree/master/java-web-bom)
