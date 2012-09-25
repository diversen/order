<?php

$f = '123.12';

echo config::getMainIni('locale');

echo "<br />\n";
echo $f = intl::formatDecimal(config::getMainIni('locale'), $f);

echo "<br />\n";

echo $f = intl::formatDecimalFromLocale(config::getMainIni('locale'), $f);

die();