/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

let temp = {};
Cu.import("resource:///modules/devtools/Toolbox.jsm", temp);
let Toolbox = temp.Toolbox;
temp = null;

function test() {
  waitForExplicitFinish();

  const URL_1 = "data:text/plain;charset=UTF-8,abcde";
  const URL_2 = "data:text/plain;charset=UTF-8,12345";

  const TOOL_ID_1 = "webconsole";
  const TOOL_ID_2 = "jsdebugger";

  const LABEL_1 = "Web Console";
  const LABEL_2 = "Debugger";

  let toolbox;

  addTab(URL_1, function () {
    let target = TargetFactory.forTab(gBrowser.selectedTab);
    gDevTools.showToolbox(target, null, Toolbox.HostType.BOTTOM)
      .then(function (aToolbox) { toolbox = aToolbox; })
      .then(function () toolbox.selectTool(TOOL_ID_1))

    // undock toolbox and check title
      .then(function () toolbox.switchHost(Toolbox.HostType.WINDOW))
      .then(checkTitle.bind(null, LABEL_1, URL_1, "toolbox undocked"))

    // switch to different tool and check title
      .then(function () toolbox.selectTool(TOOL_ID_2))
      .then(checkTitle.bind(null, LABEL_2, URL_1, "tool changed"))

    // navigate to different url and check title
      .then(function () {
        let deferred = Promise.defer();
        target.once("navigate", function () deferred.resolve());
        gBrowser.loadURI(URL_2);
        return deferred.promise;
      })
      .then(checkTitle.bind(null, LABEL_2, URL_2, "url changed"))

    // destroy toolbox, create new one hosted in a window (with a
    // different tool id), and check title
      .then(function () toolbox.destroy())
      .then(function () gDevTools.showToolbox(target, null,
                                              Toolbox.HostType.WINDOW))
      .then(function (aToolbox) { toolbox = aToolbox; })
      .then(function () toolbox.selectTool(TOOL_ID_1))
      .then(checkTitle.bind(null, LABEL_1, URL_2,
                            "toolbox destroyed and recreated"))

      .then(function cleanUp() {
        toolbox.destroy();
        gBrowser.removeCurrentTab();
        finish();
      });
  });
}

function checkTitle(toolLabel, url, context) {
  let win = Services.wm.getMostRecentWindow("devtools:toolbox");
  let definitions = gDevTools.getToolDefinitionMap();
  let expectedTitle = toolLabel + " - " + url;
  is(win.document.title, expectedTitle, context);
}
