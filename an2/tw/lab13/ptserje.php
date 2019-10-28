<?php
	include ('./db.php');
	switch ($_SERVER['REQUEST_METHOD']) {
	    case "GET":
	        if(preg_match('/\/api\/v1\/bookmarks\/?$/'
	                , $_SERVER['REQUEST_URI'])) {
	           $json_str = getBookmarks();
	       	   $json_obj = json_encode($json_str);
	       	   echo $json_obj;
	           
	        } else if(preg_match('/\/api\/v1\/bookmarks\/(.+)?$/'
	                , $_SERVER['REQUEST_URI'])) {
	            
	            $json_str = getBookmarksById();
	            $json_obj = json_decode($json_str);
	            
	            echo $json_obj -> url; //respond
	            http_response_code(200);
	        } else {
	            http_response_code(404);
	        }
	        break;
	    default:
	        break;
	}
?>

/*
	{
		"name":"doru",
		"url":"http//doru.com"
	}
*/