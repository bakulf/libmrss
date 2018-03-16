<?
dl("mrss.so");

function check ($a) {
  if(mrss_error($a)!=MRSS_OK)
  {
    echo "*** ".mrss_strerror($a)." ***\n";
    exit;
  }
}
$data=mrss_parse_url("http://ngvision.org/rss");
check($data);
print_r (mrss_get($data));
?>
