import QtQuick 2.0
import QtQuick.Window 2.2

import SceneGraphRendering 1.0

Window {
  height: 600
//  maximumHeight: height
//  minimumHeight: height

  width: 600
//  maximumWidth: width
//  minimumWidth: width

  visible: true

  // The checkers background
  /*ShaderEffect
  {
    id: tileBackground
    anchors.fill: parent

    property real tileSize: 16
    property color color1: Qt.rgba(0.9, 0.9, 0.9, 1);
    property color color2: Qt.rgba(0.85, 0.85, 0.85, 1);

    property size pixelSize: Qt.size(width / tileSize, height / tileSize);

    fragmentShader:
      "
      uniform lowp vec4 color1;
      uniform lowp vec4 color2;
      uniform highp vec2 pixelSize;
      varying highp vec2 qt_TexCoord0;
      void main() {
          highp vec2 tc = sign(sin(3.14152 * qt_TexCoord0 * pixelSize));
          if (tc.x != tc.y)
              gl_FragColor = color1;
          else
              gl_FragColor = color2;
      }
      "
  }*/

  Rectangle
  {
    width: 50
    height : 50
    color: "red"
    anchors.right: parent.right
  }

  Renderer
  {
    id: board

    anchors.left: parent.left
    width: parent.width - 50
    height: parent.height - 50
    fig_type: "board"

    MouseArea
    {
      anchors.fill: parent
      onClicked:
        console.log("x is ", mouseX, " y is: ", mouseY )
    }
  }

  Repeater
  {
    model: ContextProperty.bar

    delegate:
      Renderer
      {
        id: renderer

        width: 60
        height: 60

        x: 60 * (index + 1)
        y: 350 - 3

        fig_type: "cube"

        MouseArea
        {
          id: _dragArea

          drag.target: parent
          anchors.fill: parent
          drag.minimumX: 0
          drag.minimumY: 0

          onClicked:
          {
            renderer.width *= 1.6
            renderer.height *= 1.6
            //renderer.pressEvent()
          }
        }
      }
  }
}
