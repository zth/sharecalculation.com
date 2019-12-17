const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const outputDir = path.join(__dirname, "public/assets/");
const webpack = require("webpack");
const BundleAnalyzerPlugin = require("webpack-bundle-analyzer")
  .BundleAnalyzerPlugin;
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const ReactRefreshWebpackPlugin = require("@pmmmwh/react-refresh-webpack-plugin");
const { CleanWebpackPlugin } = require("clean-webpack-plugin");
const PreloadWebpackPlugin = require("preload-webpack-plugin");
const WorkboxPlugin = require("workbox-webpack-plugin");
const WebpackPwaManifest = require("webpack-pwa-manifest");
const FaviconsWebpackPlugin = require("favicons-webpack-plugin");
const RobotstxtPlugin = require("robotstxt-webpack-plugin");
const env = require("./env.json");

const isProd = process.env.NODE_ENV === "production";

module.exports = {
  entry: "./src/Index.bs.js",
  mode: isProd ? "production" : "development",
  output: {
    path: outputDir,
    filename: "[name].[contenthash].js",
    publicPath: "/assets/"
  },
  plugins: [
    new CleanWebpackPlugin(),
    new HtmlWebpackPlugin({
      template: "src/index.html"
    }),
    new webpack.DefinePlugin({
      __DEV__: JSON.stringify(process.env.NODE_ENV !== "production"),
      SENTRY_ID: env.sentryId,
      ANALYTICS_ID: env.analyticsId
    }),
    new MiniCssExtractPlugin({
      filename: !isProd ? "[name].css" : "[name].[hash].css",
      chunkFilename: !isProd ? "[name].[id].css" : "[name].[id].[hash].css"
    }),
    new PreloadWebpackPlugin(),
    ...(isProd
      ? [
          new RobotstxtPlugin(),
          new WorkboxPlugin.GenerateSW({
            swDest: "sw.js",
            clientsClaim: true,
            skipWaiting: true
          }),
          new FaviconsWebpackPlugin(path.resolve("src/assets/icon.png")),
          new WebpackPwaManifest({
            name: "ShareCalculation.com",
            short_name: "ShareCalc",
            description:
              "Create and share interactive calculations. When creating a spreadsheet is overkill.",
            background_color: "#f7fafc",
            theme_color: "#667eea",
            icons: [
              {
                src: path.resolve("src/assets/icon.png"),
                sizes: [96, 128, 192, 256, 384, 512] // multiple sizes
              }
            ]
          }),
          new BundleAnalyzerPlugin({ analyzerMode: "static" })
        ]
      : [])
  ],
  module: {
    rules: [
      {
        test: /\.(woff(2)?|ttf|eot|svg)(\?v=\d+\.\d+\.\d+)?$/,
        use: [
          {
            loader: "file-loader",
            options: {
              name: "[name].[hash].[ext]",
              outputPath: "fonts/"
            }
          }
        ]
      },
      {
        test: /\.(png|svg|jpg|gif)$/,
        use: ["url-loader"]
      },
      {
        test: /\.css$/,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
            options: {
              hmr: !isProd
            }
          },
          { loader: "css-loader" },
          {
            loader: "postcss-loader"
          }
        ]
      },
      {
        test: /\.m?js$/,
        exclude: /node_modules/,
        use: [
          {
            loader: require.resolve("babel-loader"),
            options: {
              plugins: isProd
                ? ["@babel/plugin-syntax-dynamic-import"]
                : ["@babel/plugin-syntax-dynamic-import"]
            }
          }
        ]
      }
    ]
  },
  optimization: {
    runtimeChunk: "single",
    moduleIds: "hashed",
    splitChunks: {
      chunks: "all",
      maxInitialRequests: Infinity,
      minSize: 0,
      cacheGroups: {
        sentry: {
          test: /[\\/]node_modules[\\/]@sentry/,
          name: "sentry",
          chunks: "all"
        },
        mathjs: {
          test: /[\\/]node_modules[\\/](mathjs|decimal\.js|complex\.js|typed-function|rematrix|fraction\.js|process|javascript-natural-sort|seed-random|escape-latex)[\\/]/,
          name: "mathjs",
          chunks: "all"
        },
        react: {
          test: /[\\/]node_modules[\\/]react/,
          name: "react",
          chunks: "all"
        }
      }
    }
  },
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 9000,
    historyApiFallback: {
      rewrites: [
        { from: "/assets/(.*)", to: "/$1" },
        { from: "/*", to: "/assets/index.html" }
      ]
    }
  }
};
