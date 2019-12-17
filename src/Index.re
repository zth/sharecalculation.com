[%bs.raw {|require("./css/style.css")|}];

[%bs.raw
  {|
  (function() {
    if ('serviceWorker' in navigator) {
   window.addEventListener('load', () => {
     navigator.serviceWorker.register('/sw.js');
  })
 }
  })()
|}
];

if (!JsUtils.devMode) {
  Sentry.(init(makeOptions(~dsn=JsUtils.sentryId, ())));

  Gtag.config(JsUtils.analyticsId, {anonymize_ip: true});
};

ReactExperimental.renderConcurrentRootAtElementWithId(
  <ErrorBoundary
    fallback={_ =>
      <div className={CssHelpers.tcss("mx-auto md:w-1/3 sm:w-full mb-32")}>
        <Title />
        <Error />
      </div>
    }
    onError={e => Js.log(e)}>
    <App />
  </ErrorBoundary>,
  "app",
);