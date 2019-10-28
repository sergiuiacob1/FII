<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>TW Checklist</title>
    <link href="https://fonts.googleapis.com/css?family=IBM+Plex+Mono" rel="stylesheet">
    <link rel="stylesheet" type="text/css" href="./style.css" />
</head>

<body>
    <header>
        <h1> 
            <span class="emoji">🚀</span> 
            TW Checklist 
            <span class="emoji">🚀</span>
        </h1>
    </header>
    <form class="form" id="loginForm" action="" method="POST">
        <div class="form-group">
            <label for="usernameInput"> Username </label>
            <input type="text" id="usernameInput" name="username" required/>
        </div>
        <div class="form-group">
            <label for="passwordInput"> Password </label>
            <input type="password" id="passwordInput" name="password" required />
        </div>
        <button type="submit" class="btn" id="loginBtn" name="submit"> Log in </button>
        <a href="/php/views/home.php" class="link"> Continue as anonymous </a>
    </form>
</body>

</html>