function getSymbols(t) {
  return t
    .filter(function(node, parent) {
      return node.type === "SymbolNode" && parent !== "fn";
    })
    .reduce(function(acc, curr) {
      if (acc.indexOf(curr.name) === -1) {
        acc.push(curr.name);
      }
      return acc;
    }, []);
}

module.exports = {
  getSymbols
};
