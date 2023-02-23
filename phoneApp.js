// JavaScript for Phone Application Demo Program
// Jim Skon, Kenyon College, 2017
var contactList = [];
const baseUrl = 'http://3.134.78.249:5004';

/* Set up events */
$(document).ready(function() {
	// Add a click event for the filter button
	document.querySelector("#filter-btn").addEventListener("click", (e) => {
		var searchStr = 	document.querySelector("#search").value;
    	findMatches(searchStr);
	});

    $(".dropdown-menu li a").click(function() {
        var selection = $(this).text();
        $(this).parents(".btn-group").find('.btn').html(selection + ' <span class="caret"></span>');
    });

	findMatches(" ");

});

/* Search and display phone functions */

// Build output table from comma delimited list
function formatMatches(json) {

    var result = '<table class="table table-success table-striped""><tr><th>First</th><th>Last</th><th>Phone</th><th>Type</th><th>Action</th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='first'>" + entry['first'] + "</td><td class='last'>" + entry['last'];
        result += "</td><td class='phone'>" + entry['phone'] + "</td><td class='type'>" + entry['type'] + "</td>";
        result += "<td><button type='button' class='btn btn-primary btn-sm edit' data-bs-toggle='modal' data-bs-target='#editContact' ";
        result += "onclick=\"editContact(" + i + ")\">Edit</button> ";
        result += "<button type='button' class='btn btn-primary btn-sm ' onclick=\"deleteContact("+ entry['ID'] +")\">Delete</button></td></tr>";
    });
    result += "</table>";

    return result;
}

function displayMatches(results) {

    contactList = results["results"];
    console.log("Results:"+JSON.stringify(contactList));
    document.getElementById("searchresults").innerHTML = formatMatches(contactList);
    
}

function findMatches(search) {
    if (search == "") search = " ";

	console.log("Search:" + search);
    fetch(baseUrl + '/phone/find/' + search, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayMatches(json))
        .catch(error => {
            {
                alert("Find Error: Something went wrong:" + error);
            }
        })
}

/* Add contact functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
    document.getElementById("addfirst").value = "";
    document.getElementById("addlast").value = "";
    document.getElementById("addphone").value = "";

    findMatches(" ");

}

function addContact() {
    console.log("Attempting to add an entry");
    console.log("Firstname:" + $('#addfirst').val());
    $('#searchresults').empty();
    fetch(baseUrl + '/phone/add/' + $('#addfirst').val() + "/" + $('#addlast').val() + "/" + $('#addphone').val() + "/" + $('#addtype').text(), {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong:" + error);
            }
        })
}


function editContact(row) {
    console.log("start edit data: "+row+JSON.stringify(contactList[row]));

    console.log("First name of record: " + contactList[row]["first"] + " " + contactList[row]["last"]);
    editid = contactList[row]["ID"];

	document.getElementById("editfirst").value = contactList[row]["first"];
	document.getElementById("editlast").value = contactList[row]["last"];
	document.getElementById("editphone").value = contactList[row]["phone"];
	document.getElementById("edittype").innerText = contactList[row]["type"];
	
	//Save ID in modal
	var modal = document.querySelector("#editContact");
	modal.setAttribute("editid",editid);

}


function updateContact() {

	// Get ID in the modal
	var modal = document.querySelector("#editContact");
	id = modal.getAttribute("editid");
	
    console.log("Attempting to edit an entry:"+id); 

    fetch(baseUrl + '/phone/update/' + id + '/' + document.getElementById("editfirst").value 
    		+ '/' + document.getElementById("editlast").value + '/' + document.getElementById("editphone").value + '/' + document.getElementById("edittype").innerText, {
                method: 'get'
            })
        .then(alert("Record for " + document.getElementById("editfirst").value + ' ' + document.getElementById("editlast").value + " updated"))
        .catch(error => {
            {
                alert("Edit Error: something went wrong:" + error);
            }
        });
        
    findMatches(" ");

}


function deleteContact(id) {

    console.log("Attempting to delete an entry:" + id);
    fetch(baseUrl + '/phone/delete/' + id, {
            method: 'get'
        })
        .then(alert("Deleted Record: " + id))
        .catch(error => {
            {
                alert("Delete Error: Something went wrong:" + error);
            }
        });
     findMatches(" ");

}


