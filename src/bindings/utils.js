var slugifyMap = {
  Å: "a",
  å: "a",
  Ä: "a",
  ä: "a",
  Ö: "o",
  ö: "o"
};

function slugify(str) {
  return str
    .slice(0, 30)
    .replace(/[åäö\s]/g, function(c) {
      return slugifyMap[c] || "-";
    })
    .replace(/[^a-zA-Z0-9-]/g, "")
    .toLowerCase();
}

function addOrigin(str) {
  return window.location.origin + str;
}

function copyToClipboardFromElement(id) {
  var el = document.getElementById(id);

  if (el) {
    el.select();
    el.setSelectionRange(0, 99999);
    document.execCommand("copy");
    return true;
  }

  return false;
}

function hideLoading() {
  var el = document.getElementById("loading");

  if (el) {
    el.classList.add("hidden");
  }
}

module.exports = {
  slugify,
  addOrigin,
  copyToClipboardFromElement,
  hideLoading
};
