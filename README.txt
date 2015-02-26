Generate flamegraphs for Drupal pages.

Requires xhprof extension and the flamegraph.pl script from https://github.com/brendangregg/FlameGraph

Set the drupal variable "flamegraphs_pl_script" to point to your copy of "flamegraph.pl" e.g. "/home/foo/Flamegraph/flamegraph.pl".

To generate a graph, add the 'flame' query parameter to the Drupal URL you want to sample.  For example, if you wanted to sample
'http://mysite.local/node/450' you would use 'http://mysite.local/node/450?flame=1'.

You can view output at "<your_site>/sites/default/files/flamegraph.svg".
