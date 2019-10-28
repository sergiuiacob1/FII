<?php 
    $doc = new DOMDocument();
    $doc->load('bike-shop.xml');

    echo $doc -> schemaValidate('bike-shop.xsd');
?>