import json


class RestAPI:
    def __init__(self, database=None):
        self.database = database

    def get(self, url, payload=None):
        if payload is not None:
            payload = json.loads(payload)
            user_names = set(payload["users"])
            users = [user for user in self.database["users"] if user["name"] in user_names]
        else:
            users = []

        if url == "/users":
            users.sort(key=lambda user: user["name"])
            return json.dumps({"users": users})

    def post(self, url, payload=None):
        payload = json.loads(payload) if payload is not None else {}

        if url == "/add":
            user = {"name": payload["user"], "owes": {}, "owed_by": {}, "balance": 0.0}
            self.database["users"].append(user)
            return json.dumps(user)
        
        elif url == "/iou":
            lender_name = payload["lender"]
            borrower_name = payload["borrower"]
            amount = payload["amount"]
            
            lender = None
            borrower = None
            
            for user in self.database["users"]:
                if user["name"] == lender_name:
                    lender = user
                elif user["name"] == borrower_name:
                    borrower = user
                if lender and borrower:
                    break
            
            self._process_iou(lender, borrower, lender_name, borrower_name, amount)
            
            return json.dumps({"users": [lender, borrower]})

    def _process_iou(self, lender, borrower, lender_name, borrower_name, amount):
        lender["balance"] += amount
        borrower["balance"] -= amount
        
        remain_lender = amount
        if borrower_name in lender["owes"]:
            if lender["owes"][borrower_name] >= remain_lender:
                lender["owes"][borrower_name] -= remain_lender
                if lender["owes"][borrower_name] == 0:
                    del lender["owes"][borrower_name]
                remain_lender = 0
            else:
                remain_lender -= lender["owes"][borrower_name]
                del lender["owes"][borrower_name]
        
        if remain_lender > 0:
            lender["owed_by"][borrower_name] = lender["owed_by"].get(borrower_name, 0) + remain_lender
        
        remain_borrower = amount
        if lender_name in borrower["owed_by"]:
            if borrower["owed_by"][lender_name] >= remain_borrower:
                borrower["owed_by"][lender_name] -= remain_borrower
                if borrower["owed_by"][lender_name] == 0:
                    del borrower["owed_by"][lender_name]
                remain_borrower = 0
            else:
                remain_borrower -= borrower["owed_by"][lender_name]
                del borrower["owed_by"][lender_name]
        
        if remain_borrower > 0:
            borrower["owes"][lender_name] = borrower["owes"].get(lender_name, 0) + remain_borrower