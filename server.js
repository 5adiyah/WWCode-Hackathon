const env = require('dotenv').config();
const DATABASE_URL = process.env.DATABASE_URL;
console.log(process.env);
const PORT = process.env.PORT || 3000;

const express = require('express');
const app = express();
const pg = require('pg');
const cors = require('cors');

const client = require('./create-db');
// client.connect();
// client.on('error', err => {
//     console.error(err);
// });

app.use(express.json());
app.use(cors());

app.get('/plants', (request, response) => {
    client.query('SELECT * FROM plants')
    .then(function(result) {
        response.send(result.rows);
    })
    .catch(function(err) {
        console.error(err);
    });
});

app.put('/plants/:name', (request, response) => {
    const plant = request.params.name;

        client.query(`
        SELECT id, light FROM plants
        WHERE name_generic=$1;
    `,
    [plant]
    )
    .then(result => {
        const choice= result.rows[0];
        console.log(choice.id);

        return client.query(`
            UPDATE choice
            SET plant_id=$1, light =$2
            WHERE id=1
        `,
        [choice.id, choice.light]
        );
    })
    .then(result => response.send(result.rows[0]))
    .catch(function(err) {
        console.error(err);
    });
});

app.get('/choice', (request, response) => {
    client.query(`
        SELECT light FROM choice
        WHERE id=1;
    `)
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