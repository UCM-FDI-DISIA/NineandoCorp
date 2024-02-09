document.addEventListener("DOMContentLoaded", function() {
    const navItems = document.querySelectorAll("nav ul li");
    const sections = document.querySelectorAll(".section");

    // Mostrar la sección de Inicio por defecto
    document.getElementById("inicio").style.display = "block";

    navItems.forEach(item => {
        item.addEventListener("click", function(e) {
            e.preventDefault(); // Evitar el comportamiento predeterminado del enlace
            const target = this.querySelector("a").getAttribute("class");
            sections.forEach(section => {
                if (section.id === target) {
                    section.style.display = "block";
                } else {
                    section.style.display = "none";
                }
            });
        });
    });
});