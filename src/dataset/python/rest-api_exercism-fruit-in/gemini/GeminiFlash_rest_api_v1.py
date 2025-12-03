import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if url == "/users":
            try:
                payload = json.loads(payload)
                user_names = payload.get("users", [])
            except (TypeError, json.JSONDecodeError):
                user_names = []

            if self.database and "users" in self.database:
                users = [user for user in self.database["users"] if user["name"] in user_names]
                users.sort(key=lambda user: user["name"])
                return json.dumps({"users": users})
            else:
                return json.dumps({"users": []})
        return None

    def post(self, url, payload=None):
        if payload is None:
            return None

        try:
            payload = json.loads(payload)
        except (TypeError, json.JSONDecodeError):
            return None

        if url == "/add":
            user_name = payload.get("user")
            if user_name:
                user = {"name": user_name, "owes": {}, "owed_by": {}, "balance": 0.0}
                if self.database is not None:
                    if "users" not in self.database:
                        self.database["users"] = []
                    self.database["users"].append(user)
                return json.dumps(user)
            else:
                return None
        elif url == "/iou":
            lender = payload.get("lender")
            borrower = payload.get("borrower")
            amount = payload.get("amount")

            if lender and borrower and isinstance(amount, (int, float)):
                lender_found = None
                borrower_found = None

                if self.database and "users" in self.database:
                    for user in self.database["users"]:
                        if user["name"] == lender:
                            lender_found = user
                        elif user["name"] == borrower:
                            borrower_found = user

                    if lender_found and borrower_found:
                        lender_found["balance"] += amount
                        borrower_found["balance"] -= amount

                        remain = amount

                        if borrower in lender_found["owes"]:
                            if lender_found["owes"][borrower] > remain:
                                lender_found["owes"][borrower] -= remain
                                remain = 0
                            else:
                                remain -= lender_found["owes"][borrower]
                                del lender_found["owes"][borrower]

                        if remain > 0:
                            if borrower not in lender_found["owed_by"]:
                                lender_found["owed_by"][borrower] = 0
                            lender_found["owed_by"][borrower] += remain

                        remain = amount

                        if lender in borrower_found["owed_by"]:
                            if borrower_found["owed_by"][lender] > remain:
                                borrower_found["owed_by"][lender] -= remain
                                remain = 0
                            else:
                                remain -= borrower_found["owed_by"][lender]
                                del borrower_found["owed_by"][lender]

                        if remain > 0:
                            if lender not in borrower_found["owes"]:
                                borrower_found["owes"][lender] = 0
                            borrower_found["owes"][lender] += remain

                        return json.dumps({"users": [lender_found, borrower_found]})
                return json.dumps({"users": []})
            else:
                return None
        return None