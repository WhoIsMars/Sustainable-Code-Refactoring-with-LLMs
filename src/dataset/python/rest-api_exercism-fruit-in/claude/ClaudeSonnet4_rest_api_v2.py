import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
            user_names = set(payload["users"])
            users = [user for user in self.database["users"]
                     if user["name"] in user_names]
        else:
            users = []

        if url == "/users":
            users.sort(key=lambda user: user["name"])
            return json.dumps({"users": users})

    def post(self, url, payload=None):
        payload = json.loads(payload) if payload is not None else {}

        if url == "/add":
            user = {"name": payload["user"],
                    "owes": {}, "owed_by": {}, "balance": 0.0}
            self.database["users"].append(user)
            return json.dumps(user)
        
        elif url == "/iou":
            lender = payload["lender"]
            borrower = payload["borrower"]
            amount = payload["amount"]
            
            # Create lookup dictionary for O(1) access
            user_lookup = {user["name"]: user for user in self.database["users"]}
            
            lender_user = user_lookup.get(lender)
            borrower_user = user_lookup.get(borrower)
            
            result_users = []
            
            if lender_user:
                lender_user["balance"] += amount
                remain = amount
                
                if borrower in lender_user["owes"]:
                    owed_amount = lender_user["owes"][borrower]
                    if owed_amount > remain:
                        lender_user["owes"][borrower] -= remain
                        remain = 0
                    else:
                        remain -= owed_amount
                        del lender_user["owes"][borrower]
                
                if remain > 0:
                    lender_user["owed_by"][borrower] = lender_user["owed_by"].get(borrower, 0) + remain
                
                result_users.append(lender_user)
            
            if borrower_user:
                borrower_user["balance"] -= amount
                remain = amount
                
                if lender in borrower_user["owed_by"]:
                    owed_amount = borrower_user["owed_by"][lender]
                    if owed_amount > remain:
                        borrower_user["owed_by"][lender] -= remain
                        remain = 0
                    else:
                        remain -= owed_amount
                        del borrower_user["owed_by"][lender]
                
                if remain > 0:
                    borrower_user["owes"][lender] = borrower_user["owes"].get(lender, 0) + remain
                
                result_users.append(borrower_user)
            
            return json.dumps({"users": result_users})