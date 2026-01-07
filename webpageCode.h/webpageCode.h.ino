const char webpageCode[] =
R"=====(
<!DOCTYPE html>

<html>

<head>
    <style>
        canvas {
            background: #48b;
        }

        body {
            font-family: 'Roboto'
        }

        .simulation {
            background-color: #269;
            padding: 20px;
        }

        .row {
            background-color: #faa;
            padding: 10px;
            display: flex;
            flex: 1;
            flex-direction: row;
        }

        .dataPanel {
            padding: 20px;
            background-color: #eee;
            flex: 1;
        }
    </style>
</head>

<body>
    <div class="main">
        <h2>
          Robot Inverse Kineamtics
        </h2>
      </div>
      
      <div class="row">
        <div id="simulation" class="simulation"></div>
        <div class="dataPanel">
          <p>End Effector X & Y is Green Dot</p>
      
          <label>Final X:</label>
          <input type="number" id="fx" name="fx" value="60"><br><br>
          <label>Final Y:</label>
          <input value="80" type="number" id="fy" name="fy"><br><br>
          <input id="button" type="submit" value="Submit">
          <br><br>
          <label>Theta 1:</label>
          <p id="theta1_label">degrees</p>
          <label>Theta 2:</label>
          <p id="theta2_label">degrees</p>
        </div>
      </div>

    <script>
        // Quadratic code
        //2 dof robot arm

        var r, x2, y2; //radius of final position and its x&y coordinates
        var theta1, theta2; // rotations of 2 joints, dependent variables
        var thi1, thi2, thi3; // other internal angles
        var a1, a2; //given lenghts of the 2 jonts

        var t1_label, t2_label; //labels for 2 joint rotations
        t1_label = document.getElementById("theta1_label");
        t2_label = document.getElementById("theta2_label");
        //save label data into URLs
        var baseUrl =window.location.origin + window.location.pathname

        
        // var myUrl = window.location.href;
        // console.log(myUrl)
        var newUrl = new URL(baseUrl);

        findRadius = (x, y) => {
            var r1 = Math.sqrt(x * x + y * y);
            console.log("radius is ", r1);
            return r1;
        };

        rad2deg = (rad) => {
            return rad * (180 / Math.PI);
        };

        //algorithm
        //first declare the lengths of the 2 joints
        //then The user selects a specific point either as XY or radius & angle(thi2)

        // Assuming X & Y coordinates are given:
        // First compute the radius
        // Then compute thi2 using pythagorus
        // Then computre thi1 using law of consines
        // Then compute theta 1 by subtracting thi1 from thi2
        // Then compute thi3 using law of consines
        // Then subtract thi3 from 180 to get theta2

        a1 = 50; //joint lengths in cm
        a2 = 50;
        x2 = 60;
        y2 = 80; // input x and y coords here

        calculateAngles = () => {
            r = findRadius(x2, y2);
            thi2 = Math.atan(y2 / x2);
            thi1 = Math.acos((a2 * a2 - a1 * a1 - r * r) / (-2 * a1 * r));
            theta1 = thi2 - thi1;
            console.log("theta 1 is", rad2deg(theta1));
            theta1_label.innerHTML = rad2deg(theta1).toFixed(1);

            thi3 = Math.acos((r * r - a1 * a1 - a2 * a2) / (-2 * a1 * a2));
            theta2 = Math.PI - thi3;
            console.log(thi3);
            console.log("theta 2 is ", rad2deg(theta2));
            theta2_label.innerHTML = rad2deg(theta2).toFixed(1);
            // newUrl.searchParams.append('theta2', rad2deg(theta2).toFixed(1))
            var refresh = baseUrl +`?theta1=${rad2deg(theta1).toFixed(1)}&thetha2=${rad2deg(theta2).toFixed(1)}&x2=${x2}&y2=${y2}` 
            // window.location.href = refresh;
            window.history.pushState({path:refresh},'',refresh)
        };

        //drawing code
        var x, y;
        y = 140 - y2;
        x = x2;
        var h = 300;
        var scale = 2.5;
        var canvas = document.createElement("canvas");
        var simulation = document.getElementById("simulation");
        simulation.appendChild(canvas);

        canvas.width = 400;
        canvas.height = h;
        var ctx = canvas.getContext("2d");
        ctx.translate(0, 0);
        //ctx.fillRect(0,0,10,10);

        placeEE = () => {
            ctx.translate(0, 0);
            ctx.beginPath();
            ctx.arc(x2 * scale, h - y2 * scale, 7, 0, Math.PI * 2);
            ctx.fillStyle = "#0f0";
            ctx.fill();
            ctx.closePath();
            ctx.lineWidth = 1;
            ctx.strokeStyle = "#000";
            ctx.stroke();
        };

        drawArm = () => {
            ctx.translate(0, 0);
            //stroke first joint
            ctx.beginPath();
            ctx.arc(0, h, 14, 0, Math.PI * 2);
            ctx.fillStyle = "#f00";
            ctx.fill();
            ctx.closePath();
            ctx.lineWidth = 1;
            ctx.stroke();

            //first leg
            ctx.beginPath();
            ctx.translate(0, h);
            ctx.moveTo(0, 0);
            ctx.rotate(-theta1); //rotate by theta1
            ctx.lineTo(a1 * scale, 0);
            ctx.lineWidth = 8;
            ctx.closePath();
            ctx.strokeStyle = "#ccc";
            ctx.stroke();

            //joint
            ctx.beginPath();
            ctx.translate(a1 * scale, 0);
            ctx.moveTo(0, 0);
            ctx.arc(0, 0, 10, 0, Math.PI * 2);
            ctx.fill();
            ctx.closePath();
            ctx.strokeStyle = "#f00";
            ctx.stroke();

            //another line
            ctx.beginPath();
            //ctx.rotate(Math.PI/4);
            ctx.moveTo(0, 0);
            ctx.rotate(-theta2);
            ctx.lineTo(a2 * scale, 0); //final end effector position
            ctx.closePath();
            ctx.lineWidth = 6;
            ctx.strokeStyle = "#ccc";
            ctx.stroke();
        };

        drawGrid = () => {
            console.log("drawgrid called");
            ctx.beginPath();
            ctx.lineWidth = 2;
            ctx.strokeStyle = "#fff3";
            for (var x = 0; x < 400; x += 10 * scale) {
                ctx.moveTo(x, 0);
                ctx.lineTo(x, h);
            }
            for (var y = 0; y < h; y += 10 * scale) {
                ctx.moveTo(0, y);
                ctx.lineTo(400, y);
            }
            ctx.closePath();
            ctx.stroke();
        };

        function getMousePosition(canvas, event) {
            let rect = canvas.getBoundingClientRect();
            let x = event.clientX - rect.left;
            let y = event.clientY - rect.top;

            x = x / scale;
            y = (h - y) / scale
            //console.log("Coordinate x: " + x, "Coordinate y: " + y);

            x2 = x;
            y2 = y;
            updateCanvas();
        }

        canvas.addEventListener("mousedown", function (e) {
            getMousePosition(canvas, e);
        });

        updateCanvas = () => {
            ctx.resetTransform();
            ctx.clearRect(0, 0, 400, h);
            drawGrid();
            calculateAngles();
            placeEE();
            drawArm();
        }

        submitButton = () => {
            x2 = parseInt(document.getElementById("fx").value);
            y2 = parseInt(document.getElementById("fy").value);

            updateCanvas();
        };


        document.getElementById("button").onclick = submitButton;

        //code to refresh the page adn save the params in the url
        const queryString = window.location.search;
        const urlParams = new URLSearchParams(queryString);
        console.log(queryString);
        if(urlParams.has("x2")){
            console.log("has params!")
            x2= urlParams.get('x2');
            y2 = urlParams.get('y2');

            updateCanvas();
        }
    </script>
</body>

</html>
  )=====";
