-- Keep a log of any SQL queries you execute as you solve the mystery.

-- check schema of the database
.schema

-- check crime scene reports on 2021-07-28 on Humphrey Street
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- check interviews on that date
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- show suspected list in bakery. Has license plate present
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = "exit";

-- check phone logs in that time frame:
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- atm records
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";

-- tie bank account no with ppi
SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street");

-- find people who overlap with the above info. Suspects down to Diana and Bruce.
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street")) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = "exit");

-- find airport code for fiftyville. ID = 8
SELECT * FROM airports WHERE city = "Fiftyville";

-- find flights on July 29 2021 with origin ID of 8
SELECT * FROM flights WHERE origin_airport_id = "8" AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

-- earlies flight is ID  36. Match passport numbers with the suspect list.
SELECT * FROM people INNER JOIN passengers ON passengers.passport_number = people.passport_number WHERE passengers.flight_id = 36 AND passengers.passport_number IN (SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street")) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = "exit"));

-- Culprit is Bruce find accomplice based on phone call: It's Robin
select * from people where phone_number = "(375) 555-8161";