window.addEventListener("DOMContentLoaded", (event) => {
    const button = document.createElement("button");
    button.innerText = "Show Inheritance Diagram";
    button.classList.add("show-inheritance-button");
    
    const content = document.getElementsByClassName("content")[0];
    content.insertBefore(button, content.firstChild);

    const inheritanceDiagram = document.querySelector(".inheritance");

    button.addEventListener("click", () => {
        if (inheritanceDiagram.style.display === "none") {
            inheritanceDiagram.style.display = "block";
            button.innerText = "Hide Inheritance Diagram";
        } else {
            inheritanceDiagram.style.display = "none";
            button.innerText = "Show Inheritance Diagram";
        }
    });
});
