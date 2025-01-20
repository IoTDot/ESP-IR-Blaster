#ifndef WEB_UI_H
#define WEB_UI_H

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP Wi-Fi Manager</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #f4f4f4;
        }
        .container {
            background: #fff;
            width: 100%;
            max-width: 400px;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 8px;
            text-align: center;
        }
        .container h1 {
            margin-bottom: 20px;
            color: #333;
            font-size: 24px;
        }
        .form-group {
            margin-bottom: 15px;
            text-align: left;
        }
        .form-group label {
            font-weight: bold;
            color: #555;
            margin-bottom: 5px;
            display: inline-block;
        }
        .form-group input {
            width: calc(100% - 10px);
            padding: 10px;
            font-size: 14px;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        button {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            color: #fff;
            background-color: #007BFF;
            border: none;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP Wi-Fi Manager</h1>
        <form action="/setwifi" method="POST">
            <div class="form-group">
                <label for="ssid">SSID</label>
                <input type="text" id="ssid" name="ssid" placeholder="Enter Wi-Fi SSID" required>
            </div>
            <div class="form-group">
                <label for="password">Password</label>
                <input type="password" id="password" name="password" placeholder="Enter Wi-Fi Password" required>
            </div>
            <button type="submit">Submit</button>
        </form>
    </div>
</body>
</html>
)rawliteral";

const char SETWIFI_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Wi-Fi Settings Saved</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #f4f4f4;
        }
        .container {
            background: #fff;
            width: 100%;
            max-width: 400px;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 8px;
            text-align: center;
        }
        .container h1 {
            margin-bottom: 20px;
            color: #333;
            font-size: 24px;
        }
        .container p {
            color: #555;
            font-size: 16px;
            margin-bottom: 10px;
        }
        .countdown {
            font-size: 18px;
            font-weight: bold;
            color: #FF0000;
        }
        .restarted {
            font-size: 24px;
            font-weight: bold;
            color: #FF0000;
            animation: blink 1s infinite;
        }
        @keyframes blink {
            0% { opacity: 1; }
            50% { opacity: 0; }
            100% { opacity: 1; }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Wi-Fi Settings Saved</h1>
        <p id="restart-message">The device will restart in <span id="countdown" class="countdown">5</span> seconds...</p>
        <p>Please reconnect to the new network.</p>
    </div>
    <script>
        let countdown = 5;
        const countdownElement = document.getElementById('countdown');
        const restartMessage = document.getElementById('restart-message');
        const interval = setInterval(() => {
            countdown--;
            if (countdown > 0) {
                countdownElement.textContent = countdown;
            } else {
                clearInterval(interval);
                restartMessage.innerHTML = "<span class='restarted'>RESTARTED</span>";
            }
        }, 1000);
    </script>
</body>
</html>
)rawliteral";

#endif
