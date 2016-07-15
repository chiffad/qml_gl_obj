import QtQuick 2.0
 import QtQuick.Window 2.2
import SceneGraphRendering 1.0

Window
{
  width: 400
  height: 400
  visible: true

  // The checkers background
  ShaderEffect
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
  }

  Renderer
  {
    id: renderer
    anchors.fill: parent
    anchors.margins: 10

    MouseArea
    {
      id: mouse
      anchors.fill: parent

      onClicked:
        renderer.pressEvent()
    }
  }
}
