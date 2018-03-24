const express = require('express');
const pg = require('pg');
const PORT = 3000;

const app = express();

const client = new pg.Client('postgres://postgres:grrrrr@LOCALHOST:5432/plants')
client.connect();
client.on('error', error => {
  console.error(error);
});

app.use(express.json());

app.get('/plants', (request, response) => {
    client.query('SELECT * FROM plants')
    .then(function(result) {
        response.send(result.rows);
    })
    .catch(function(err) {
        console.error(err);
    });
});

app.listen(PORT, () => {
    console.log(`Server started on port ${PORT}!`);
  });