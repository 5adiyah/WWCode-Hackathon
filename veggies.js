'use strict';


let veggieChoice = null;

const form = document.getElementById('veggies');

const formInit = () => {
    form.addEventListener('submit', (e) => {
        e.preventDefault();

        if (document.getElementById('basil').checked) {veggieChoice = "Basil"};
        if (document.getElementById('carrot').checked) {veggieChoice = "Carrot"};
        if (document.getElementById('kale').checked) {veggieChoice = "Kale"};
        if (document.getElementById('spinach').checked) {veggieChoice = "Spinach"};
        if (document.getElementById('tomato').checked) {veggieChoice = "Tomato"};
        if (document.getElementById('tree').checked) {veggieChoice = "Tree"};

        sendChoice(veggieChoice)
        console.log(veggieChoice);
        form.reset();
    })
};

function sendChoice(choice) {
    return $.ajax({
        url: `${DATABASE_URL}/plants/${choice}`,
        method: 'PUT',
    })
};
