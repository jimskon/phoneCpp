// JavaScript for Phone Application Demo Program
// Jim Skon, Kenyon College, 2017
var editid;
const baseUrl = 'http://3.134.78.249:5004';

$(document).ready(function () {
    $('.editdata').hide();
    $("#search-btn").click(getMatches);
    $("#add-btn").click(addEntry);
    $(".start-edit").click(startAdd);
    $(".end-edit").click(endAdd);
    $("#clear").click(clearResults);

	$(".dropdown-menu li a").click(function(){
		var selection =$(this).text();
		$(this).parents(".btn-group").find('.btn').html(selection+' <span class="caret"></span>');
	});
	
	endAdd();

});


function startAdd(){
	console.log("Add Entry");
	$('#addmessage').empty();
	$('.inputdata').show();
	$('.searchbox').hide();
	$('.results').hide();
	$('.editdata').hide();
	$('#searchresults').empty();
}

function endAdd() {
	console.log("End add");
	$('.editdata').hide();
	$('.inputdata').hide();
	$('.results').show();
	$('.searchbox').show();
	$('#searchtype').html('Find Last'+' <span class="caret"></span>')
   
}

// Build output table from comma delimited list
function buildTable(json) {

	var result = '<table class="table table-success table-striped""><tr><th>First</th><th>Last</th><th>Phone</th><th>Type</th><th>Action</th><tr>';
	json.forEach(function (entry,i) {
	    result += "<tr><td class='first'>"+entry['first']+"</td><td class='last'>"+entry['last']+"</td><td class='phone'>"+entry['phone']+"</td><td class='type'>"+entry['type']+"</td>";
	    result += "<td><button type='button' ID='"+entry["ID"]+"' class='btn btn-primary btn-sm edit'>Edit</button> ";
	    result += "<button type='button' ID='"+entry['ID']+"' class='btn btn-primary btn-sm delete'>Delete</button></td></tr>";
	});
	result += "</table>";
	
	return result;
}

function startEdit(){
    console.log("start edit data");
    $('#searchresults').empty();
    $('.editdata').show();
    $("#edit-btn").click(editProcess);
    console.log("Edit Record: " + $(this).attr('ID'));
    var row=$(this).parents("tr");
    console.log("First name of record: "+ $(row).find('.first').text()+":"+$(row).find('.type').text());
    editid=$(this).attr('ID');

    $('#editfirst').val( $(row).find('.first').text());
    $('#editlast').val( $(row).find('.last').text());
    $('#editphone').val( $(row).find('.phone').text());
    $('#edittype').text( $(row).find('.type').text());
    $('.editdata').show();
}

function editDone() {
    $('#editmessage').text($('#editfirst').val()+" "+$('#editlast').val()+ " SAVED");
}
function editProcess(){
    console.log("Attempting to edit an entry");
    console.log("Firstname:" + $('#editfirst').val() + "ID:" + editid);
    $('#searchresults').empty();
        fetch(baseUrl+'/phone/update/'+editid+'/'+$('#editfirst').val()+'/'+
        $('#editlast').val()+'/'+$('#editphone').val()+'/'+$('#edittype').text(), {
		method: 'get'
    })
	.then (editDone())
	.catch(error => {
	    {alert("Error: Edit - something went wrong:"+error);}
	})

}


function processDelete(){
    
    $('#searchresults').empty();
    var id=$(this).attr('ID');
    console.log("Attempting to delete an entry:"+id);
    fetch(baseUrl+'/phone/delete/'+id, {
		method: 'get'
    })
	.then (alert("Deleted Record: " +id ))
	.catch(error => {
	    {alert("Error: Something went wrong:"+error);}
	})
	
}
function processFind(results) {

	var phonelist = results["results"];
    //console.log("Results:"+JSON.stringify(phonelist));
    $('#searchresults').empty();
    $('#searchresults').append(buildTable(phonelist));
    $(".edit").click(startEdit);
    $(".delete").click(processDelete);
}

function clearResults() {
    $('#searchresults').empty();
}

function getMatches(){
    $('.editdata').hide();
    $('#searchresults').empty();
    var search = $('#search').val();
    var selection = $('#searchtype').text().trim().split(" ");
    var field = selection[1].toLowerCase();
	// ignore if this is "add entry"
	if (field == "entry") return
	
    fetch(baseUrl+'/phone/'+field+'/'+search, {
		method: 'get'
    })
	.then (response => response.json() )
    .then (json => processFind(json))
	.catch(error => {
	    {alert("Error: Something went wrong:"+error);}
	})
}

function processAdd(results) {
    $('#addmessage').empty();
    console.log("Add:",results["status"]);
    $('#addmessage').text($('#addfirst').val()+" "+$('#addlast').val()+ " ADDED");
    $('#addfirst').val('');
    $('#addlast').val('');
    $('#addphone').val('');
    
}

function addEntry(){
    console.log("Attempting to add an entry");
    console.log("Firstname:" + $('#addfirst').val());
    $('#searchresults').empty();
    fetch(baseUrl+'/phone/add/'+$('#addfirst').val()+"/"+$('#addlast').val()+"/"+$('#addphone').val()+"/"+$('#addtype').text(), {
		method: 'get'
    })
	.then (response => response.json() )
    .then (json => processAdd(json))
	.catch(error => {
	    {alert("Error: Something went wrong:"+error);}
	})
}



    
