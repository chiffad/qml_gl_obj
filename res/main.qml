/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Window 2.2

import SceneGraphRendering 1.0

Window {
  height: 600
  maximumHeight: height
  minimumHeight: height

  width: 600
  maximumWidth: width
  minimumWidth: width

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
    id: board

    anchors.fill: parent
    fig_type: "board"

    MouseArea
    {
      anchors.fill: parent
      onClicked:
        console.log("x is ", mouseX, " y is: ", mouseY )
    }
  }

  Row
  {
    Repeater
    {
      model: 3

      delegate:
        Renderer
        {
          id: renderer

          width: 60
          height: 60

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
}
