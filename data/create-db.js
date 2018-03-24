'use strict';

const pg = require('pg');
const fs = require('fs');
// const plantsData = require('./plants.json');

const client = new pg.Client('postgres://postgres:grrrrr@LOCALHOST:5432/plants');
client.connect();

const readJson = (path, cb) => {
    fs.readFile(require.resolve(path), (err, data) => {
        if (err)
        cb(err)
        else
        cb(null, JSON.parse(data))
    })
};

client.query(`
    CREATE TABLE IF NOT EXISTS plants (
        id SERIAL PRIMARY KEY,
        name_generic VARCHAR(30) NOT NULL,
        name_scientific VARCHAR(30) NOT NULL,
        category VARCHAR(15),
        light VARCHAR(15) NOT NULL,
        soil VARCHAR(15)
    );
`)
    .then(
        () => console.log('plant table created'),
        err => console.error(err)
    );

readJson('./plants.json', (err, plantsData) => {
    plantsData.map(plant => {
        client.query(`
            INSERT INTO plants (
                name_generic, 
                name_scientific,
                category,
                light,
                soil)
                VALUES ($1, $2, $3, $4, $5);
            `,
        [
            plant.name_generic, plant.name_scientific, plant.category, plant.light, plant.soil
        ])
    .then (
        () => console.log('plant table seeded'),
        err => console.error(err)
        )
    })
});

//Figure out how to end this client
