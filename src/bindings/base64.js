var ENC = {
  "+": "-",
  "/": "_",
  "=": "."
};
var DEC = {
  "-": "+",
  _: "/",
  ".": "="
};

function encode(base64) {
  return base64.replace(/[+/=]/g, m => ENC[m]);
}

function decode(safe) {
  return safe.replace(/[-_.]/g, m => DEC[m]);
}

module.exports = {
  encode,
  decode
};
