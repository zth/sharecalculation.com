type options = {anonymize_ip: bool};

let config: (string, options) => unit = [%bs.raw
  {|
function config(id, opts) {
    gtag("config", id, opts);
}
|}
];