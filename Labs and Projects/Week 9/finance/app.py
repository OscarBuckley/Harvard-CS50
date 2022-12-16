import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    if request.method == "POST":
        return render_template("index.html")
    else:
        return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # ensure symbol is valid
        if not lookup(request.form.get("symbol")):
            return apology("stock does not exist", 400)

        # buying negative number of stocks error
        if request.form.get("shares") <= 0:
            return apology("cannot buy negative number of stocks", 400)

        # assign values
        stocks = lookup(request.form.get("symbol"))
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # get cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]

        if (stocks["price"] * shares) < cash:
            return apology("not enough money", 403)
        else:
            db.execute("UPDATE users SET cash WHERE id = ?;", cash - (stocks["price"] * shares), session["user_id"])
            db.execute("INSERT INTO transactions (user_id, symbol, shares, cash, date) VALUES ?, ?, ?, ?, ?;",
                        session["user_id"], symbol, shares, (stocks["price"] * shares), datetime.now())

        # go to index
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # if POST
    if request.method == "POST":

        # get quote into variable
        quotes = lookup(request.form.get("symbol"))

        # return apology if lookup failed
        if quotes is None:
            return apology("Stock does not exist", 400)

        # pass variables
        name = quotes["name"]
        price = quotes["price"]
        symbol = quotes["symbol"]

        # return result to new template
        return render_template("quoted.html", name=name, price=price, symbol=symbol)

    else:

        # show default quote html
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # empty value handling errors
        if not request.form.get("username"):
            return apology("must provide username", 400)

        if not request.form.get("password"):
            return apology("must provide password", 400)

        # password did not match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("please re-enter your password correctly", 400)

        # check if username is taken
        if request.form.get("username") in db.execute("SELECT username FROM users;")[0]["username"]:
            return apology("username already taken", 400)

        # write input into variables
        username = request.form.get("username")
        hash = generate_password_hash(password=request.form.get("password"))

        # insert into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, hash)

        # prepare session token
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        # show register.html if get request
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # else:
    # return render_template("login.html")
