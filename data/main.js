const toggleButtonOn = () => {
    const xhttp = new XMLHttpRequest();
    xhttp.open("GET", "start", true);
    xhttp.send();
}

const toggleButtonOff = () => {
    const xhttp = new XMLHttpRequest();
    xhttp.open("GET", "stop", true);
    xhttp.send();
}