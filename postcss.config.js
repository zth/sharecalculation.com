const purgecss = require("@fullhuman/postcss-purgecss")({
  content: ["./src/**/*.html", "./src/**/*.re"],
  defaultExtractor: content =>
    (content.match(/(?<=tcss\([\s]*").*(?="[\s\S]*\))/g) || []).flatMap(s =>
      s.split(" ").map(v => v.trim())
    )
});

module.exports = {
  plugins: [
    require("tailwindcss"),
    require("autoprefixer"),
    ...(process.env.NODE_ENV === "production"
      ? [
          purgecss,
          require("cssnano")({
            preset: "default"
          })
        ]
      : [])
  ]
};
