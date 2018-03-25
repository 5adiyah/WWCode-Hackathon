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
        id VARCHAR(3) PRIMARY KEY,
        name_generic VARCHAR(30) NOT NULL,
        light VARCHAR(15) NOT NULL
    );
`)
    .then(
        () => console.log('plant table created'),
        err => console.error(err)
    );

readJson('./data/plants.json', (err, plantsData) => {
    plantsData.map(plant => {
        client.query(`
            INSERT INTO plants (
                id,
                name_generic, 
                light)
                VALUES ($1, $2, $3);
            `,
        [
            plant.id, plant.name_generic, plant.light
        ])
    .then (
        () => console.log('plant table seeded'),
        err => console.error(err)
        )
    })
});

client.query(`
    CREATE TABLE IF NOT EXISTS choice (
        id SERIAL,
        plant_id VARCHAR(3) REFERENCES plants(id),
        light VARCHAR(15) NOT NULL
    );
`)
    .then(
        () => console.log('choice table created'),
        err => console.error(err)
    );

client.query(`
            INSERT INTO choice (
                plant_id,
                light)
                VALUES ($1, $2);
            `,
        [
            "ORI", "semi-shade"
        ])
    .then (
        () => console.log('default choice seeded'),
        err => console.error(err)
    );

//Figure out how to end this client
