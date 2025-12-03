import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if url == "/users":
            if payload:
                try:
                    payload = json.loads(payload)
                    user_names = payload.get("users", [])
                except (json.JSONDecodeError, AttributeError):
                    return json.dumps({"users": []})  # Handle invalid payload gracefully
            else:
                return json.dumps({"users": []})

            users = [user for user in self.database["users"] if user["name"] in user_names]
            users.sort(key=lambda user: user["name"])
            return json.dumps({"users": users})
        return None  # Or raise an exception for unhandled URLs

    def post(self, url, payload=None):
        if payload:
            try:
                payload = json.loads(payload)
            except (json.JSONDecodeError, TypeError):
                return None  # Or raise an exception for invalid payload
        else:
            return None  # Or raise an exception if payload is required

        if url == "/add":
            user_name = payload.get("user")
            if user_name:
                user = {"name": user_name, "owes": {}, "owed_by": {}, "balance": 0.0}
                self.database["users"].append(user)
                return json.dumps(user)
            else:
                return None # Or raise exception if user is required
        elif url == "/iou":
            lender_name = payload.get("lender")
            borrower_name = payload.get("borrower")
            amount = payload.get("amount")

            if lender_name and borrower_name and isinstance(amount, (int, float)):
                lender = None
                borrower = None

                for user in self.database["users"]:
                    if user["name"] == lender_name:
                        lender = user
                    elif user["name"] == borrower_name:
                        borrower = user

                if lender and borrower:
                    lender["balance"] += amount
                    borrower["balance"] -= amount

                    # Update lender's owes/owed_by
                    remain = amount
                    if borrower_name in lender["owes"]:
                        if lender["owes"][borrower_name] > remain:
                            lender["owes"][borrower_name] -= remain
                            remain = 0
                        else:
                            remain -= lender["owes"][borrower_name]
                            del lender["owes"][borrower_name]

                    if remain > 0:
                        if borrower_name not in lender["owed_by"]:
                            lender["owed_by"][borrower_name] = 0
                        lender["owed_by"][borrower_name] += remain

                    # Update borrower's owes/owed_by
                    remain = amount
                    if lender_name in borrower["owed_by"]:
                        if borrower["owed_by"][lender_name] > remain:
                            borrower["owed_by"][lender_name] -= remain
                            remain = 0
                        else:
                            remain -= borrower["owed_by"][lender_name]
                            del borrower["owed_by"][lender_name]

                    if remain > 0:
                        if lender_name not in borrower["owes"]:
                            borrower["owes"][lender_name] = 0
                        borrower["owes"][lender_name] += remain

                    return json.dumps({"users": [lender, borrower]})
                else:
                    return None # Or raise exception if lender or borrower not found
            else:
                return None # Or raise exception if lender, borrower, or amount are missing/invalid
        return None  # Or raise an exception for unhandled URLs