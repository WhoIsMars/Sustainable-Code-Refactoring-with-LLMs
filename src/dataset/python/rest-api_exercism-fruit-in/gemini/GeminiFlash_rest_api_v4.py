import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if url == "/users":
            try:
                payload = json.loads(payload)
                user_names = payload.get("users", [])
            except (json.JSONDecodeError, AttributeError):
                user_names = []

            users = [user for user in self.database["users"] if user["name"] in user_names]
            users.sort(key=lambda user: user["name"])
            return json.dumps({"users": users})

    def post(self, url, payload=None):
        try:
            payload = json.loads(payload)
        except (json.JSONDecodeError, TypeError):
            payload = {}

        if url == "/add":
            user_name = payload.get("user")
            if user_name:
                user = {"name": user_name, "owes": {}, "owed_by": {}, "balance": 0.0}
                self.database["users"].append(user)
                return json.dumps(user)
            else:
                return json.dumps({"error": "User name is required"})

        elif url == "/iou":
            lender = payload.get("lender")
            borrower = payload.get("borrower")
            amount = payload.get("amount")

            if not all([lender, borrower, amount]):
                return json.dumps({"error": "Lender, borrower, and amount are required"})

            lender_user = None
            borrower_user = None

            for user in self.database["users"]:
                if user["name"] == lender:
                    lender_user = user
                elif user["name"] == borrower:
                    borrower_user = user

            if not lender_user or not borrower_user:
                return json.dumps({"error": "Lender or borrower not found"})

            lender_user["balance"] += amount
            borrower_user["balance"] -= amount

            def update_iou(user, other_user_name, amount_key, owed_key):
                remain = amount
                if other_user_name in user[amount_key]:
                    if user[amount_key][other_user_name] > remain:
                        user[amount_key][other_user_name] -= remain
                        remain = 0
                    else:
                        remain -= user[amount_key][other_user_name]
                        del user[amount_key][other_user_name]

                if remain > 0:
                    if other_user_name not in user[owed_key]:
                        user[owed_key][other_user_name] = 0
                    user[owed_key][other_user_name] += remain

            update_iou(lender_user, borrower, "owes", "owed_by")
            update_iou(borrower_user, lender, "owed_by", "owes")

            return json.dumps({"users": [lender_user, borrower_user]})