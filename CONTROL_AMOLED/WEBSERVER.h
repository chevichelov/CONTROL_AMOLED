#pragma once
#include <Arduino.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADf9f7/3/T+/+D1/f/g9f3/4PX9/+D1/f/G8d7/wfDY/8Dx2P/I8uH/w/LX/8jy3P/l+P7/5fj+/+f6/v/V7vz/4fb+/+H2/v/h9v7/3/b7/7/w1f/C8dj/3Pb3/+H2/v/h9/3/2/b0/8Ty1/+88c3/wPLP/9/48//i9v7/e6Xb/+L3/v/i9/7/2PXx/73x0v/i9v3/4vf+/+L3/v/i9/7/4vj+/+L4/v/l+P7/5fj7/8Hyzv++8sr/pc7q/z5lmv/k9/7/4ff8/73x0f/j9/7/5Pf+/+T3/v/k+P7/5fj+/+T4///k+P//5fj//+b5/v/o+f7/xfPP/6Lbxf9kj8b/5Pf+/8Py1v/k9/z/5ff+/+X4///m+P7/3uXk/9jX0v/c4+H/4Orr/+X2+//m+f//6fr+/+j6+P/A8sr/uuTe/+T3/f/D8tf/5ff9/+X3/v/m+P7/5vj+/+Dp6f/W0sj/1M7E/827qv/c4t//5vn+/+n6/v/p+/7/yfTW/9P22v/S9Of/wuTt/5u++f+Lsfn/ss/7/77Z+//P5vz/3PH8/+P2/f/n+f3/5/n9/+f6/v/p+v//6vv+/9L24P/q+vX/xvLb/9Xr/P+bvfn/ZpT6/5G1+f+Tt/r/gar5/5G1+f+PtPn/mbz5/6TE+v+kxfv/sc77/9Dm/P/p+vn/0vbe/8by2v/m+P7/5vj+/93x/P/M5Pz/xN77/67N/P+uzPr/m736/57A+v+QtPn/qMf6/2+b+f9/p/r/0un0/9X34f/Y9ev/0fTm/+b5/v/n+f7/6Pn+/+f5/v/n+f//5/n//+n4/f/p+f3/4vT9/9/y/f++2Pz/v9r7/7bi2f/u+/v/xfLW/8Xy1f/n+f7/6Pn//+n5///o+f//6Pn//+j5///p+f//6fn//+n5///q+v//7Pv+/+z7/v/L9Nb/8Pz+/9L15P+98cv/4Pf0/+j5///p+f//6vn//+n5///p+f//6fn//+n5///q+v//6vr//+z7/v/g+e//1vbj//D8/v/q+P7/wvLQ/8Hyz//n+Pz/6vn//+v5///q+f//6fn//+n5///p+f//6vr//+v6/v/o+vj/yfTT/+77/v/w/P7/6vn+/+b4+/+98cr/wvLP/9/38P/s+v7/6/r//+v6///r+f//6vn//+r6/v/c9+3/yfPT/+/7/v/v+/7/8Pz+/+v4///q+P//6fn8/8Xy0v++8cn/yvPW/8v02f/V9uT/1Pbk/8v02P/K89f/2Pbl/+76/v/v+///7/v+//D8/v/s+f//6/n//+z5/v/s+v7/3ffr/8702v/t+f3/4/jx/+P48//t+v7/7fn+/+76/v/u+v7/7/v//+/7/v/w/P7/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==" type="image/x-icon" />
    <style>
      body {
        margin: 0 0 0 0;
        padding: 0 0 0 0;
      }
      @media screen and (max-width:1300px) {
        #menu {
          background:#fffbef;
          height:3rem;
          weight:100%;
        }
        #menu img {
          height:3rem;
          float:left;
          margin:0 0.5rem 0 0;
        }
        #menu span{
          font-family:'Open Sans', sans-serif;
          font-size:1.2rem;
          font-weight:700;
          color:#6789ba;
          line-height:3rem;
        }
        #head{
          margin:3rem 0 3rem 0;
          font-family:'Open Sans', sans-serif;
          font-size:1.5em;
          text-align:center;
        }
        @media screen and (max-width:800px) {
          #main{
            font-family:'Open Sans', sans-serif;
            font-size:6em;
            text-align:center;
          }
        }
        @media screen and (min-width:800px) {
          #main{
            font-family:'Open Sans', sans-serif;
            font-size:10em;
            text-align:center;
          }
        }
        #menu_smoll{
          float:right;
        }
        #menu_smoll a{
          font-size:5em;
          line-height:3rem;
          margin:0 1rem 0 0;
          text-decoration:none;
          color:#000;
        }
        #select_smoll{
          position:absolute;
          right:0;
          background:#fffbef;
          height:100%;
          padding:0 0.5rem 0 1em;
          z-index: 999999;
        }
        #select_smoll a{
          display:block;
          margin:3rem;
          font-family:'Open Sans', sans-serif;
          font-size:1rem;
          color:#000;
          font-weight:100;
          -webkit-font-smoothing:antialiased;
          -webkit-text-size-adjust:100%;
          bottom:10px;
          letter-spacing:4px;
          font-size:1rem;
          text-transform:uppercase;
          text-decoration:none;
          font-weight:700;
        }
        #select{
          display:none;
        }
      }
      @media screen and (min-width:1300px) {
        #menu{
          background:#fffbef;
          height:3rem;
          weight:100%;
        }
        #menu img{
          height:3rem;
          float:left;
          margin:0 0.5rem 0 0;
        }
        #menu span{
          font-family:'Open Sans', sans-serif;
          color:#6789ba;
          line-height:3rem;
          font-weight:700;
          font-size:2rem;
        }
        #head{
          margin:3rem 0 3rem 0;
          font-family:'Open Sans', sans-serif;
          font-size:2em;
          text-align:center;
        }
        #main{
          font-family:'Open Sans', sans-serif;
          font-size:15em;
          text-align:center;
        }
        #select{
          float:right;
        }
        #select a{
          margin-top:1rem;
          font-family:'Open Sans', sans-serif;
          font-size:1rem;
          line-height:2rem;
          color:#000;
          font-weight:100;
          -webkit-font-smoothing:antialiased;
          -webkit-text-size-adjust:100%;
          bottom:10px;
          letter-spacing:4px;
          font-size:1rem;
          text-transform:uppercase;
          text-decoration:none;
          font-weight:700;
        }
        #select a{
          display:inline-block;
          position:relative;
          padding:0 1rem 0 1rem;
          transition:color .35s ease;
        }
        #select a:before{
          content:'';
          display:block;
          position:absolute;
          left:0;
          bottom:0;
          height:2px;
          width:0;
          transition:width 0s ease, background .35s ease;
        }
        #select a:after{
          content:'';
          display:block;
          position:absolute;
          right:0;
          bottom:0;
          height:2px;
          width:0;
          background:#000;
          transition:width .35s ease;
        }
        #select a:hover:before{
          width:100%;
          background:#000;
          transition:width .35s ease;
        }
        #select a:hover:after{
          width:100%;
          background:transparent;
          transition:all 0s ease;
        }
        #menu_smoll, #select_smoll{
          display:none;
        }
      }
      .c3 svg {
        font: 10px sans-serif;
        -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
      }
      .c3 path, .c3 line {
        fill: none;
        stroke: #000;
      }
      .c3 text {
        -webkit-user-select: none;
        -moz-user-select: none;
        user-select: none;
      }
      .c3-legend-item-tile,
      .c3-xgrid-focus,
      .c3-ygrid,
      .c3-event-rect,
      .c3-bars path {
        shape-rendering: crispEdges;
      }
      .c3-chart-arc path {
        stroke: #fff;
      }
      .c3-chart-arc rect {
        stroke: white;
        stroke-width: 1;
      }
      .c3-chart-arc text {
        fill: #fff;
        font-size: 13px;
      }
      .c3-grid line {
        stroke: #aaa;
      }
      .c3-grid text {
        fill: #aaa;
      }
      .c3-xgrid, .c3-ygrid {
        stroke-dasharray: 3 3;
      }
      .c3-text.c3-empty {
        fill: #808080;
        font-size: 2em;
      }
      .c3-line {
        stroke-width: 1px;
      }
      .c3-circle {
        fill: currentColor;
      }
      .c3-circle._expanded_ {
        stroke-width: 1px;
        stroke: white;
      }
      .c3-selected-circle {
        fill: white;
        stroke-width: 2px;
      }
      .c3-bar {
        stroke-width: 0;
      }
      .c3-bar._expanded_ {
        fill-opacity: 1;
        fill-opacity: 0.75;
      }
      .c3-target.c3-focused {
        opacity: 1;
      }
      .c3-target.c3-focused path.c3-line, .c3-target.c3-focused path.c3-step {
        stroke-width: 2px;
      }
      .c3-target.c3-defocused {
        opacity: 0.3 !important;
      }
      .c3-region {
        fill: steelblue;
        fill-opacity: 0.1;
      }
      .c3-region text {
        fill-opacity: 1;
      }
      .c3-brush .extent {
        fill-opacity: 0.1;
      }
      .c3-legend-item {
        font-size: 12px;
      }
      .c3-legend-item-hidden {
        opacity: 0.15;
      }
      .c3-legend-background {
        opacity: 0.75;
        fill: white;
        stroke: lightgray;
        stroke-width: 1;
      }
      .c3-title {
        font: 14px sans-serif;
      }
      .c3-tooltip-container {
        z-index: 10;
      }
      .c3-tooltip {
        border-collapse: collapse;
        border-spacing: 0;
        background-color: #fff;
        empty-cells: show;
        -webkit-box-shadow: 7px 7px 12px -9px #777777;
        -moz-box-shadow: 7px 7px 12px -9px #777777;
        box-shadow: 7px 7px 12px -9px #777777;
        opacity: 0.9;
      }
      .c3-tooltip tr {
        border: 1px solid #CCC;
      }
      .c3-tooltip th {
        background-color: #aaa;
        font-size: 14px;
        padding: 2px 5px;
        text-align: left;
        color: #FFF;
      }
      .c3-tooltip td {
        font-size: 13px;
        padding: 3px 6px;
        background-color: #fff;
        border-left: 1px dotted #999;
      }
      .c3-tooltip td > span {
        display: inline-block;
        width: 10px;
        height: 10px;
        margin-right: 6px;
      }
      .c3-tooltip .value {
        text-align: right;
      }
      .c3-area {
        stroke-width: 0;
        opacity: 0.2;
      }
      .c3-chart-arcs-title {
        dominant-baseline: middle;
        font-size: 1.3em;
      }
      .c3-chart-arcs .c3-chart-arcs-background {
        fill: #e0e0e0;
        stroke: #FFF;
      }
      .c3-chart-arcs .c3-chart-arcs-gauge-unit {
        fill: #000;
        font-size: 16px;
      }
      .c3-chart-arcs .c3-chart-arcs-gauge-max {
        fill: #777;
      }
      .c3-chart-arcs .c3-chart-arcs-gauge-min {
        fill: #777;
      }
      .c3-chart-arc .c3-gauge-value {
        fill: #000;
      }
      .c3-chart-arc.c3-target g path {
        opacity: 1;
      }
      .c3-chart-arc.c3-target.c3-focused g path {
        opacity: 1;
      }
      .c3-drag-zoom.enabled {
        pointer-events: all !important;
        visibility: visible;
      }
      .c3-drag-zoom.disabled {
        pointer-events: none !important;
        visibility: hidden;
      }
      .c3-drag-zoom .extent {
        fill-opacity: 0.1;
      }
      .range {
        place-items: center;
        height: 2em;
        width: 50%;
        background: #fff;
        border-radius: 10px;
        margin-left: auto;
        margin-right: auto;
      }
      .range .field {
        position: relative;
        display: flex;
        align-items: center;
        justify-content: center;
        height: 100%;
      }
      .range .field .value {
        position: absolute;
        font-size: 5em;
        font-weight: 600;
        color: #000;
      }
      .range .field .value.left {
        left: -1em;
      }
      .range .field .value.right {
        right: -2em;
      }
      .range .field input {
        -webkit-appearance: none;
        height: 3px;
        width: 100%;
        background: #ddd;
        border-radius: 5px;
        outline: none;
        border: 0;
        margin: 0 10px;
      }
      .range .field input::-webkit-slider-thumb {
        -webkit-appearance: none;
        width: 5em;
        height: 5em;
        background: #000;
        border-radius: 50%;
        border: 3px solid #fff;
        cursor: pointer;
      }
    </style>
</head>
<body>
  <div id="menu">
    <span>
      <img alt="youtube.com/@chevichelov" border="0" src="data:image/x-icon;base64,/9j/4RciRXhpZgAASUkqAAgAAAAMAAABAwABAAAAoAAAAAEBAwABAAAAoAAAAAIBAwADAAAAngAAAAYBAwABAAAAAgAAABIBAwABAAAAAQAAABUBAwABAAAAAwAAABoBBQABAAAApAAAABsBBQABAAAArAAAACgBAwABAAAAAgAAADEBAgAfAAAAtAAAADIBAgAUAAAA0wAAAGmHBAABAAAA6AAAACABAAAIAAgACACA/AoAECcAAID8CgAQJwAAQWRvYmUgUGhvdG9zaG9wIDI0LjcgKFdpbmRvd3MpADIwMjQ6MDk6MjMgMTY6MDQ6MDUAAAQAAJAHAAQAAAAwMjMxAaADAAEAAAD//wAAAqAEAAEAAACgAAAAA6AEAAEAAACgAAAAAAAAAAAABgADAQMAAQAAAAYAAAAaAQUAAQAAAG4BAAAbAQUAAQAAAHYBAAAoAQMAAQAAAAIAAAABAgQAAQAAAH4BAAACAgQAAQAAAJwVAAAAAAAASAAAAAEAAABIAAAAAQAAAP/Y/+0ADEFkb2JlX0NNAAL/7gAOQWRvYmUAZIAAAAAB/9sAhAAMCAgICQgMCQkMEQsKCxEVDwwMDxUYExMVExMYEQwMDAwMDBEMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMAQ0LCw0ODRAODhAUDg4OFBQODg4OFBEMDAwMDBERDAwMDAwMEQwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAz/wAARCACgAKADASIAAhEBAxEB/90ABAAK/8QBPwAAAQUBAQEBAQEAAAAAAAAAAwABAgQFBgcICQoLAQABBQEBAQEBAQAAAAAAAAABAAIDBAUGBwgJCgsQAAEEAQMCBAIFBwYIBQMMMwEAAhEDBCESMQVBUWETInGBMgYUkaGxQiMkFVLBYjM0coLRQwclklPw4fFjczUWorKDJkSTVGRFwqN0NhfSVeJl8rOEw9N14/NGJ5SkhbSVxNTk9KW1xdXl9VZmdoaWprbG1ub2N0dXZ3eHl6e3x9fn9xEAAgIBAgQEAwQFBgcHBgU1AQACEQMhMRIEQVFhcSITBTKBkRShsUIjwVLR8DMkYuFygpJDUxVjczTxJQYWorKDByY1wtJEk1SjF2RFVTZ0ZeLys4TD03Xj80aUpIW0lcTU5PSltcXV5fVWZnaGlqa2xtbm9ic3R1dnd4eXp7fH/9oADAMBAAIRAxEAPwD1JJJJRrlJJJJKUkqmX1KnHeKWh1+U4SzHr1dH77/za6/+EegfYs3M93ULvTqP/aTHJaI/4bI0ts/sekxMM9aiOIj/ABY/3pMUsupjAcchvXyx/vz/AJTTZHVsGh/pb/Vu/wBDSDY/T+RXu2/20bFvsvrL7KH4+sNbZt3Efvfo3P2qscnpfTQMasNY86jHpbuef+tVAv8A89R+1dWv/o+I2hp4fkv1/wC2aN//AJ9TRMg6ys/uQHFX96X/ALDWDKRL1SEiP8nijx8P9+X/ALCdFJZ/2Pqlmtuf6Y/doqa3/pXeu9I9Ksdq7qGWT5PY3/qak7jl+4fqY/8AfL/cydMUvqcY/wC6k6CSzh0q1v0OoZY/rOY7/qqk/wBl6tXrVnNtHZt9TT/06DQlxy6wP0Mf++V7k+uKX0MD/wB26CSz/tvUqP6Vh+o0c2Yzt/8A4DYKrf8AM9VWMXqGHlktpsBsb9Kt0te3+tU/a9qQyRJq6PaXpP8AzkxzQJ4b4ZfuzHBL6CXzNhJJJPZFJJJJKUkkkkp//9D1JJJJRrlLOuzb8u5+J087RWdt+WRLWH/RUj/C3/8AgdSbLuuzcg4GI4srZ/S8lvLZ/wC09P8Aw7/z3/4Fn8tEtto6dTVi4tW60+3HxmaTHL3n82tv+FtUUpcV0agPml1l/Ug155OK6PDiianMfNOX+bxf99/gY1mtwOkY+5xg2GC90vttef8Ap22OUBX1HO1uLsHGPFTCPWcP+FtEtp/qVfpP+FRMTAdXYcrLeL8xwgvj2sH+ix2fmM/8EsV1KMSQARwx6QH/AHaYYzIAEe3jHy4o6f8Ahko/9CP/AD0ONh4uIwsx6xWDqSOXHxe8+97v66MkkpAABQFDwZoxERUQAB0GgUkkkklSSSSSlKvlYGJlx69e5zdWWCWvb/UsZD2f5ysJIEAiiLHiiUYyFSAkOx1c/d1HA+lOfijl0frDB8B7Mn/oW/8AGK5jZNGVS27HeLK3cOH5D+65EVHIwbGXHNwCK8g/ztR/m7h4Wj8239y9NqUdrlH939L/AASxGM8esbnDrA6zj/cl+l/ck30lXw8yvLrLmgssYdttTtHMd+48KwnggiwyxkJASibBUkkkil//0fUlS6nlW1tZjYuuXkksqPOwf4TIf/IparjnBrS4mABJJWd0xpyX2dTtHuyPbjg8toafZ/29/PvVeZOkRoZdf3Y/pFZlJNY4mpT3I/Rxx+eX/cxZk4/ScFrGgvIIaxs++21//VWWv+mpYGHZVuyMpwszLtbXjho/Noq/4Kv/AKf84g4f69lu6g7WiomvDHY/m3ZP/XP5qv8A4P8A4xaSEADUv0RpjH/d/wDercURIiYFY4aYY9K+X3P8L/J/6v8AvqSSSUjOpJJJJSkkkklKSSSQUpJJJJSk6ZOipo52Nc14zsITlViH1nQXM70v/l/6B/5j1ZxsmrKobfUZY8SJ5H7zXD99n5yKs1w/Z/UBY0RiZzoeBwy8/Rs/q5H0Hf8AC/10w+k8X6J+bz/f/wC/YZfq58Y+SZqY/dl0yf8Aqx0kkklIzP8A/9L0LrLi+qrAYYfnPFRjkVj35Dv+2m7P7aXU3uZjMw8c7Lcpwor2/mtj9K8f8VQ16K7Gsd1MZTyPSrp9Opo53OdutedP3WVtQa/1jrNj+W4VQrb/AF7Yts/8CZUqkrJl0MyMY/uD5v8A1IwTEiZ3ocshhj/so+qZ/wDSzdqqZVUyqsBrKwGsA7AaBTSSUrZAAFDopJJJJSkkkklKSSSSUpJJJJSkkkklKTpkkVLoOZjMy8azHfo2wQCOQeWPb/KY/wB6MkgQCCDsUSiJAxOoIohqdMyX5OI11sC+smq8DtYw7LP876atrPp/V+sX1cMy6xe0dt7P0N3/AEPQWghAnho7x9J/wev+Ex4STCpG5QJhL/B/S/w/nf/T9SPCzuj++m/JmTkZFr58muNDP+hUtB52sc7wBKodEbt6RiedTXH+17z+VV5fzkfKR+vpWS1zQHQRnL/C9Ef+6k3k6ZIkNBLjAAklOZl0kGzLxa2sc+1rW2nbWZEOPg1CzupYuC1jsgkCydgaJmIn8qBlEAkkCt10cc5EARJMtgBvW7bSWSfrBQca2+umyKtpDXw3cC4MJa73/Q3tTZfWzXRiWUMBdlO1D5O0e3f9Hb++me9jq76X+PCyDlcxIHBVkx1/eEeP/ouuksm3qWS3q1eMABS6tjnMjXc9wYff/I3Kr1G7Ny+pW4VNzqGUN0FcgucWG7XYWu/kISzADQEni4K/rJhysiRxERjwe6Zb8MHfJABJMAclDfkY7Hsrfa1rrf5tpIl0fufvLByMjIu+rdrcnW1jmMcTz/ONID/5e1VbbqrXYNTXhxYyxh1Gm8ubUyf8z2JsuYqqG4jLX+vLhI/wWWHImV3L5ZTgeEcQ/Vw44z4v6z0Wb1TDwS1uQ8hzxLQ1pOg+AQWdax7MO7KrY8ijXY8bS7jVv0/bqs3r2RWzq1G6XCtkPDefdujb9FWc+6h/RL7ceg1+oGtsBAa5slp/SfvfT/N/fQOWXFk1FQB0r1fL/wB8octDgwExkTmMblfoHFP5a/uOlg5YzMZl4bs3AS3mCQHc/nfSWLm9Y6k+692G5tdGKSCCAXO2ubW8+4O/Pf8AyFo9CJPTmAAhwAEng+1sQVgtLvsfUHvjcXODiOJdbRMIZZy9uGpFxMiR6fliv5bDD3stxEhGUYREvV883R6n1G9/TMTMqc6omxvqhhIH0fU26fmKD7bMvrmMN0mmtkxxuP8AOn/MeoW0WP8Aq1uLtKyx7QByPax2/wDqb/am6Ax2TnvynHYR+7/JDWuYd272v3scmEyOSAN+vgl/isohCOHJIV+qOXGP8Ph4f+6dbqUV5fT8jiLzST5Wsc2P+3WVLQVDrWmGx/8Ao76HD/t2sfxV9W4/PMd+GX2+n/uHFhplyDvwz/xhwf8AqJ//1PULBNbh4ghUuimek4n/ABLB+CvnhZ3RPbgCmZOPZbSf7Fjw0f5m1V5fzkf7sv8AuFh/noeMJ/8ASxtLq1mTkdSq6fXa6mrY17iwwSXO2axH0EOi3L/YmbRmSXVMIBfqYdptcU9xbX9Y3Oe+WitriXR7QNr47e3RPd1A9R6JkWW1BhYAWjkau2N5/O0VYkGWQkni/WDh6GMQ7ABEMMREGH6mRl+lGc5f87jc1+RUcbCqDwXMtD3j90bama/2mvV7r9ja39PZBLqwXEAf8WBtP0XO9ioWU1114FjQA6zc4nT8xtR/6ovd7lo9frNVuEKqia6WPAbW0wPoAAbQdqjF8GS/9WP+iznh97DV6+8ddNfXFsWPoyuj5L6MY1WbDvYWgP8AaZDnHT9z1Fj4zjkXYlbR6grYZYND7opLBu/qset7peX9sqtrdjNx2iRtYQRBEe6Aza5UOh9KysbM35DI2CJExwREuDd3P5iklEzljI1EtJGuH5ZcTBjyRxxziXplE8UImXF88eCuJe71j9ZDq1xDWQNQNssIB+l7mTv/AJajXZ9n6znXPPqejL5dAmK3wzQeba1oO6bb+2PtwcCxwALeIgD47vcxLN6Dh5mR9ocXMe76YHDoEf1v8xOOOepA1GQyAJ6d1gz4fTGR9MsMccjEbS9Nx/5rR6nmDP6Ecl9Yre2wQJmDP5p0/MKqOxaa87DrYI9Vr9w+dtY/6LV0R6dinEGI5k1DXWOf3uNqkMHGiuWbjVq0yZ53+6I3+/3IywSkQSRdQ18Yy9S2HOQhExiJCPFkoX+jkjww/wAVxetE09Xpe2l1lddIGxg0ibPZwUa22zqHRcirHxvReCyKmxEb2vd/o/fsZvctl9VbyC9gcRwXAGPhKkAAIAgDsneybn6vTO7FfveLH96HDi9HrxcNSMjXolxfK4nSH9WrdXTbUBjtERtcD295e8bfo/uKN31cudc/07/1a1+91Rkd5gkTv/zVvJI+xExEZEyrayj73kEzOAjj4vmAG/8AW/vNcYNP2I4bpNbmlrjwTOrj/J9zlDp3TasBrxWZ3xPhp8S9XElJwRsGtYigWH3J8Mo8R4ZnikP3pd2h1vXA293XUAf9u1K+qHVve7CoH+EyWEj+TWHZB/8APSvpR+eR8Ix/7r/u2vDXLkPYQh9RxT/9SP8A/9X1JZ2J+h6nm450bbsya/7Q9G3/AKdX/TWis7qn6vbjdQGjaHenef8AgrPa53/W7PTtVfLoBL9w2f7vyyWZtBHJ/m5cR/uH0T/xYy41Z/RsPOsFtgIsAguaeQP3gjV9PxWYpxQwGl30g7Wf9YVlJLgjZlQs7tk5chjGPGeGPyi/la4wcUUiksljZIB8+R/U/kfQRnMa+N4BjUSJUkkQANgtMpHck/2qSSSRQpIlc3bf1N3Sb+oOySa76pZW32vY83BjPQLA12z0Ts+nv3qt1HKOR03MZZvq+05xYGWyXNbXVXbsLG7/AM9imGAk/MN+E1+LGcvh0eptycand6trK9jDY8OIEMHNhH7n8tCd1LCY81m0F4srpc0AmH2/zQOn5y5brN11h+2V6tdgU12jyyPV/wDRjWI76rf256rDNNme2uwDs6htdtf/AJ8tTxgFWT0J/wAXh0WnIeg6u0Ot0ux35LKLjS0sa2xzQ1ry94o/Ry7d7XO/dWkuWwmXv6EKa68m25r6LH1WMLWiLRa9mNvDPzWe73LpKLH21NssqdS53NT4Lm699hez/pKPLAR26SI/71dCRO/a0qSQSUS9dJJQe9tbXPeQ1rQS4nsBqSkotJ36frbGxLMOkvJ/l3HYz/wKqxWmZTH5VmKAd9TWvce0PLto/rexVekgnHszrRtdmON5B/NrgNoaf6tDWJdHBtruznCHZlhsb4+mP0eP/wCBN3pkCdP9YTM/3P0f/UbWxyNxrfNKWWX+yA4Yf+oX/9b1JRtqZdW6qwbmPBa5p7giCpJKJJF6FzumWPYH4F5m/Ehocfz6j/M2/wCaNln/AAqvqp1HFtcWZmKJy8edrZgWMP8AOUP/AK/+D/csRcXJqy6G3V/RdoWnRzXD6Vbx+a9n5yjj6TwHp8v9aH/oLHiPCfalvH5D+/j/AO+h8s0ySZOnMykkkkVORT9XaWVPqtyLLGwyuogNaWV12DJbVw7fus/nHq4zpmG243bSXl9lklxjda1tdvt/qM2q2knHJM7laIRHRrswMKtmxlDA3a2sgtB9tetTDun+b/NRwAJgROphOkmkk7m0gAKSSSSSukmTpKXWd1Gcu6vpjD7bP0mWR2pB/m5/fyH+z/i/VVjNzG4tO+DZa87Kahy95+iwf9//AHEPFqbgY1uTlvHrP/S5do4kD6DP+Dqb+jqTZ1L0dN5n+r+7/hNfKeI+3+jV5T+7j/d/w/8AoI+rOdY2vptWj8yWPI/MpH8+/g/mfo2f11frY2tja2Da1oAaBwAFR6ZVZc9/VLwW25IAqYfzKR7qmf1n/wA7YtBKGtzP6Xy/3B8v+N8ycQJJyEUZ6RH7uOPy/wCN87//1/UkkklGuUs/Kxrsa52bhN37v6TjD/CAf4Sv93IZ/wCCrQSTZREh+R7LZwEh2I1jIfNGXcNfGyacqoW0u3NOhHBBHLHt/Me1FVTK6c71XZeC8UZZHvmTXZHDb2D/AM+s/SJqOpMNgxstn2XKPDHn2v8AOiz6Fv8A58/kJnEQanp2l+jJbHKYnhy+k7CX+Tn/AN7L+o3UkyScyrpJkklLpJJklLpJJJKXVfLzKcSsPfLnOO2upur3u7MrYgW9T9R5o6ewZNw0c+YpYf8Ahbh+d/wVf6RPRiV4pfmZlvq5Ee+9/taxv7lTfo01f6vTTK9I/WX6Mf8AvmCWUysY+nzZD/Nw/wC/krDxbjac/PI+0kEMrBllLP3GH86x3+Ht/wC+IQH7Xva869NodLQeL7B+e797Hq/N/wBLYm/SdYiN1XTTqZlr7x/1VeN/5+Wo1rWNDWgNa0QANAAEIxEhQ+Tez/lT/wB5/wBP/ZrMcBMAC/a+biPzcxL94/6v/wBKf7JdJJJTNl//0PUkkklGuUkkkkpSHfj0ZFZqvY2ys8tcJCIkgQCKOqCARRFg9C546fl439CyT6YBjHyAbG+TWXSL6/8Awb/i0xz8mkxmYdrQD/O0/pmR+97Nt3/gK0Ukz26+UmPh80fs/wC9Y/a4f5uRh/V+eH+LL5f+p8Dns6z0p8j7Sytw0LbD6Z/zbtjlYblYzxLbWEeIcP70Z9bLG7bGh7fBwkfiq7uldLdO7DoJPJ9Nv/kUOHJ3ifth/wB+n9eOsJfSWP8A9WMn5eJWNz762tHJc9o/iq7utdLadrchtjjw2qbT91IejM6V0xhluJSCOCK2z/1KstYxg2saGjwAgJcOTvEfQz/7xH689YR+ksn/AKrc77fm3aYmE8A6C3IPpN+Oz33/APgSX7Ovydeo5BuYeceoGur+3qbbf7dmz+QrOW7MYGjEpba5x1L37Gt8z7Xucqv7Pz8n+nZMMPNOPNbT5Osk3u/7cTDE3REsn/Mx/wDoX/jjHKJJ4ZCeY9j+rwfX9+P/AIczsz8TFIxMSv1rm6NxqAPb/wAYf5qhv/GKNfT78qxt3UnB+0zXis/mW/umyf6Rb/X/AEf8hXcfFx8asVY9bamD81oj70VPGMmuPp+gPk/9CXjEZV7hBA2xx/m4+f8AnP5fq1JJJKVmUkkkkp//2f/tHuRQaG90b3Nob3AgMy4wADhCSU0EBAAAAAAADxwBWgADGyVHHAIAAAIAAAA4QklNBCUAAAAAABDNz/p9qMe+CQVwdq6vBcNOOEJJTQQ6AAAAAAD3AAAAEAAAAAEAAAAAAAtwcmludE91dHB1dAAAAAUAAAAAUHN0U2Jvb2wBAAAAAEludGVlbnVtAAAAAEludGUAAAAASW1nIAAAAA9wcmludFNpeHRlZW5CaXRib29sAAAAAAtwcmludGVyTmFtZVRFWFQAAAABAAAAAAAPcHJpbnRQcm9vZlNldHVwT2JqYwAAABUEHwQwBEAEMAQ8BDUEQgRABEsAIARGBDIENQRCBD4EPwRABD4EMQRLAAAAAAAKcHJvb2ZTZXR1cAAAAAEAAAAAQmx0bmVudW0AAAAMYnVpbHRpblByb29mAAAACXByb29mQ01ZSwA4QklNBDsAAAAAAi0AAAAQAAAAAQAAAAAAEnByaW50T3V0cHV0T3B0aW9ucwAAABcAAAAAQ3B0bmJvb2wAAAAAAENsYnJib29sAAAAAABSZ3NNYm9vbAAAAAAAQ3JuQ2Jvb2wAAAAAAENudENib29sAAAAAABMYmxzYm9vbAAAAAAATmd0dmJvb2wAAAAAAEVtbERib29sAAAAAABJbnRyYm9vbAAAAAAAQmNrZ09iamMAAAABAAAAAAAAUkdCQwAAAAMAAAAAUmQgIGRvdWJAb+AAAAAAAAAAAABHcm4gZG91YkBv4AAAAAAAAAAAAEJsICBkb3ViQG/gAAAAAAAAAAAAQnJkVFVudEYjUmx0AAAAAAAAAAAAAAAAQmxkIFVudEYjUmx0AAAAAAAAAAAAAAAAUnNsdFVudEYjUHhsQFIAAAAAAAAAAAAKdmVjdG9yRGF0YWJvb2wBAAAAAFBnUHNlbnVtAAAAAFBnUHMAAAAAUGdQQwAAAABMZWZ0VW50RiNSbHQAAAAAAAAAAAAAAABUb3AgVW50RiNSbHQAAAAAAAAAAAAAAABTY2wgVW50RiNQcmNAWQAAAAAAAAAAABBjcm9wV2hlblByaW50aW5nYm9vbAAAAAAOY3JvcFJlY3RCb3R0b21sb25nAAAAAAAAAAxjcm9wUmVjdExlZnRsb25nAAAAAAAAAA1jcm9wUmVjdFJpZ2h0bG9uZwAAAAAAAAALY3JvcFJlY3RUb3Bsb25nAAAAAAA4QklNA+0AAAAAABAASAAAAAEAAgBIAAAAAQACOEJJTQQmAAAAAAAOAAAAAAAAAAAAAD+AAAA4QklNBA0AAAAAAAQAAAAeOEJJTQQZAAAAAAAEAAAAHjhCSU0D8wAAAAAACQAAAAAAAAAAAQA4QklNJxAAAAAAAAoAAQAAAAAAAAACOEJJTQP1AAAAAABIAC9mZgABAGxmZgAGAAAAAAABAC9mZgABAKGZmgAGAAAAAAABADIAAAABAFoAAAAGAAAAAAABADUAAAABAC0AAAAGAAAAAAABOEJJTQP4AAAAAABwAAD/////////////////////////////A+gAAAAA/////////////////////////////wPoAAAAAP////////////////////////////8D6AAAAAD/////////////////////////////A+gAADhCSU0ECAAAAAAAEAAAAAEAAAJAAAACQAAAAAA4QklN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IiB4bXA6Q3JlYXRlRGF0ZT0iMjAyNC0wOS0yM1QxNTo0ODoxOCswNTowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAyNC0wOS0yM1QxNjowNDowNSswNTowMCIgeG1wOk1vZGlmeURhdGU9IjIwMjQtMDktMjNUMTY6MDQ6MDUrMDU6MDAiIHhtcE1NOkRvY3VtZW50SUQ9IkY5OTdDMkQzRDZGNzdFNUU3MzIxNzVEMzVDNTU0RkI5IiB4bXBNTTpJbnN0YW5jZUlEPSJ4bXAuaWlkOjM4NmE5ZDMzLTU3NmItYTU0ZS1hZWI0LTk1YzRmODEzNGMzMyIgeG1wTU06T3JpZ2luYWxEb2N1bWVudElEPSJGOTk3QzJEM0Q2Rjc3RTVFNzMyMTc1RDM1QzU1NEZCOSIgZGM6Zm9ybWF0PSJpbWFnZS9qcGVnIiBwaG90b3Nob3A6Q29sb3JNb2RlPSIzIj4gPHhtcE1NOkhpc3Rvcnk+IDxyZGY6U2VxPiA8cmRmOmxpIHN0RXZ0OmFjdGlvbj0ic2F2ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6ZjkzOTlkZGEtOTVlNS0wYjRkLWE5MGUtMTdjYTExN2I5NTMyIiBzdEV2dDp3aGVuPSIyMDI0LTA5LTIzVDE2OjAyOjI4KzA1OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjQuNyAoV2luZG93cykiIHN0RXZ0OmNoYW5nZWQ9Ii8iLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249InNhdmVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOjM4NmE5ZDMzLTU3NmItYTU0ZS1hZWI0LTk1YzRmODEzNGMzMyIgc3RFdnQ6d2hlbj0iMjAyNC0wOS0yM1QxNjowNDowNSswNTowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDI0LjcgKFdpbmRvd3MpIiBzdEV2dDpjaGFuZ2VkPSIvIi8+IDwvcmRmOlNlcT4gPC94bXBNTTpIaXN0b3J5PiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAg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" />
      youtube.com/@chevichelov
    </span>
    <div id="select">
      <a href="#" class="link" alt="tester" >TESTER</a>
      <a href="#" class="link" alt="measurement" >MEASUREMENT</a>
      <a href="#" class="link" alt="oscilloscope" >OSCILLOSCOPE</a>
      <a href="#" class="link" alt="voltmetr" >VOLTMETR</a>
      <a href="#" class="link" alt="ohmmeter" >OHMMETER</a>
      <a href="#" class="link" alt="generator" >GENERATOR</a>
    </div>
    <div id="menu_smoll">
      <a href="#" id="menu_show">≡</a>
    </div>
    <div id="select_smoll" style="display: none;">
      <a href="#" class="link" alt="tester" >TESTER</a>
      <a href="#" class="link" alt="measurement" >MEASUREMENT</a>
      <a href="#" class="link" alt="oscilloscope" >OSCILLOSCOPE</a>
      <a href="#" class="link" alt="voltmetr" >VOLTMETR</a>
      <a href="#" class="link" alt="ohmmeter" >OHMMETER</a>
      <a href="#" class="link" alt="generator" >GENERATOR</a>
    </div>
  </div>
  <div id="head"></div>
  <div id="main"></div>
  <center>
    <canvas id="chart" width="990" height="500" style="display: none;"></canvas>
  </center>
  <div class="range" id="range" style="display: none;">
    <div class="field">
      <div class="value left">0</div>
      <input type="range" id="generator" min="0" , max="255" value="50" steps="1" />
      <div class="value right">255</div>
    </div>
  </div>
  <script type="application/javascript"> 
    Array.prototype.max = function() {
      return Math.max.apply(null, this);
    };
    
    function map(data, minIn, maxIn, minOut, maxOut){
      return Math.floor((data - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut);
    }
  
    var canvas    = document.getElementById('chart');
    canvas.width  = 990;
    canvas.height = 500;
    var chart     = canvas.getContext('2d');
    chart.translate(0.5, 0.5);
    chart.scale(1, 1);
    
    function line(x1, y1, x2, y2, color) {
      chart.beginPath();
      chart.strokeStyle = color;
      chart.lineWidth = 1;
      chart.moveTo(x1, y1);
      chart.lineTo(x2, y2);
      chart.stroke();
    }
    
    var indentY = 5;
    var indentX = 40;
    var x = canvas.width;
    var y = canvas.height - indentY;
    
    var getAttribute = 'tester';
    var values = [];  
    const slideValue = document.getElementById("main");
    const inputSlider = document.getElementById("generator")

    inputSlider.oninput = function() {
      const spanValue = inputSlider.value;
      slideValue.textContent = spanValue;
      slideValue.style.left = `${20 + (this.clientWidth - 20) / 100 * (spanValue / 255)}px`;
      slideValue.classList.add("show");
    };

    document.getElementById('menu_show').addEventListener('click', () => {
      document.getElementById('select_smoll').style.display = document.getElementById('select_smoll').style.display === 'none' ? 'block' : 'none';
      event.preventDefault();
    });
    window.addEventListener('resize', (e) => {
      if (window.innerWidth > 1300){
      document.getElementById('select_smoll').style.display = 'none';
      }
    });
    
    var oscilloscope = false;
    var generator = false;
    document.querySelectorAll('.link').forEach( el => {
      el.addEventListener('click', () => {
      document.getElementById('select_smoll').style.display = 'none';
      getAttribute = el.getAttribute('alt');
      load(getAttribute);
      event.preventDefault();
      })
    });
    
    function load(alt) {
      var trueRequest = new XMLHttpRequest();
      trueRequest.open('GET', '/' + alt, true);
      trueRequest.onload = function() {
        JSON.parse(this.response, function (key, value) {
        if (key == 'head'){
          if (value == 'oscilloscope') {
            oscilloscope  = true;
            generator     = false;
            document.getElementById('main').style.display = 'none';
            document.getElementById('range').style.display = 'none';
            document.getElementById('chart').style.display = 'block';
            document.getElementById('head').innerHTML = 'OSCILLOSCOPE';
          } else if (value == 'generator') {
            generator     = true;
            oscilloscope  = false;
            document.getElementById('chart').style.display = 'none';
            document.getElementById('main').style.display = 'block';
            document.getElementById('range').style.display = 'block';
            document.getElementById('head').innerHTML = 'GENERATOR';
          } else {
            document.getElementById('head').innerHTML = value;
            oscilloscope  = false;
            generator     = false;
            document.getElementById('range').style.display = 'none';
            document.getElementById('main').style.display = 'block';
            document.getElementById('chart').style.display = 'none';
          }
        } else if (key == 'main'){
          if (oscilloscope) {
            chart.clearRect(0, 0, canvas.width, canvas.height);
    
            line(indentX, 0, indentX, y, '#000000');
            line(indentX, y, x, y, '#000000');
            
            var maxChart = values.max();
            console.log(values);
            
            for (var i = indentY; i <= x; i = i + 10) {
              line(i + indentX, y, i + indentX, y + indentY, '#000000');
            }
            for (var i = 0; i <= y; i = i + 50) {
              line(indentX - 5, i, indentX, i, '#000000');
              chart.fillText(((maxChart / 100) / (y / (y - i))).toFixed(2), indentX - ((String(((maxChart / 100) / (y / (y - i))).toFixed(2)).length * 5) + 10), (i == 0 ? 5 : i) + 3);
            }
            chart.fillText((0).toFixed(2), indentX - 30, y);
            
            var y1 = 0;
            values.forEach((value, key) => {
              line((key * 2) + indentX, y-map(y1, 0, maxChart, 0, y), (key * 2) + indentX + 2, y-map(value, 0, maxChart, 0, y), '#000000');
              y1 = value;
            });
            values = [];
          } else {
            if (generator) {
              document.getElementById('generator').value = value;
            }
            document.getElementById('main').innerHTML = value;
          }
        } else if (!isNaN(value)){
          values.push(value);
        }
        });
      };
      trueRequest.send();
    };
    
    var trueRequest = new XMLHttpRequest();
    trueRequest.open('GET', '/mode', true);
    trueRequest.onload = function() {
      getAttribute = this.response;
      load(getAttribute);
    }
    trueRequest.send();
    setInterval(function() {load(getAttribute);}, 1000);
  </script>
</body>
</html>
)rawliteral";
