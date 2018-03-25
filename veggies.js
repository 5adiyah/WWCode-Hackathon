'use strict';


let veggieChoice = null;

const form = document.getElementById('veggies');

const formInit = () => {
    form.addEventListener('submit', (e) => {
        e.preventDefault();

        if (document.getElementById('basil').checked) {veggieChoice = "basil"};
        if (document.getElementById('carrot').checked) {veggieChoice = "carrot"};
        if (document.getElementById('kale').checked) {veggieChoice = "kale"};
        if (document.getElementById('spinach').checked) {veggieChoice = "spinach"};
        if (document.getElementById('tomato').checked) {veggieChoice = "tomato"};
        if (document.getElementById('tree').checked) {veggieChoice = "tree"};

        console.log(veggieChoice);
        form.reset();
    })
};

formInit();
