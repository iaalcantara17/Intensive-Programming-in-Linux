<?php
require 'vendor/autoload.php';
$mongoClient      = new MongoDB\Client('mongodb://localhost:27017');
$stocksCollection = $mongoClient->market->most_active;
$validFields      = ['Symbol','Name','Price','Change','Volume'];
$sortField        = (isset($_GET['sort']) && in_array($_GET['sort'],$validFields))
                    ? $_GET['sort']
                    : 'Symbol';
$cursor           = $stocksCollection->find([],
                    ['sort'=>[$sortField=>1]]);
echo '<!DOCTYPE html>';
echo '<html>';
echo '<head>';
echo '<meta charset="utf-8">';
echo '<title>Most Active Stocks</title>';
echo '</head>';
echo '<body>';
echo '<table border="1">';
echo '<tr>';
echo '<th>Index</th>';
foreach (['Symbol','Name','Price','Change','Volume'] as $field) {
    echo '<th><a href="?sort='.$field.'">'.$field.'</a></th>';
}
echo '</tr>';
$index = 1;
foreach ($cursor as $doc) {
    echo '<tr>';
    echo '<td>'.$index.'</td>';
    echo '<td>'.$doc['Symbol'].'</td>';
    echo '<td>'.$doc['Name'].'</td>';
    echo '<td>'.$doc['Price'].'</td>';
    echo '<td>'.$doc['Change'].'</td>';
    echo '<td>'.$doc['Volume'].'</td>';
    echo '</tr>';
    $index++;
}
echo '</table>';
echo '</body>';
echo '</html>';

