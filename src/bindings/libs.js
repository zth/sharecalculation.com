var React = require("react");

export function useDynamicLibrary(importer) {
  var [lib, setLib] = React.useState(null);
  var promiseRef = React.useRef(null);

  if (!promiseRef.current) {
    console.log(promiseRef);
    console.log("Current");
    promiseRef.current = importer().then(m => {
      console.log("m", m);
      setLib(m);
    });
  }

  if (lib) {
    return lib;
  }

  console.log(promiseRef.current);

  throw promiseRef.current;
}

export function importKaTex() {
  return import(
    /* webpackChunkName: "katex", webpackPreload: true */ "./katex"
  );
}
