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

setInterval(() => {
    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = () => {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("status").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "brightness", true);
    xhttp.send();
}, 1000)