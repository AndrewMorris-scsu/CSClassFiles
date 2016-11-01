--5.2.5
Select Distinct C1.sid
FROM Catalog C1,
   (Select C.pid, AVG(C.cost) AvgCost
    FROM Catalog C
    GROUP BY C.pid) Temp
 WHERE C1.pid = Temp.pid
 AND C1.cost > Temp.avgCost;

--5.2.8
Select S1.sid
FROM Suppliers S1, Catalog C1, Parts P1
WHERE S1.sid = C1.sid AND C1.pid = P1.pid
AND P1.color = 'Red'
INTERSECT
Select S2.sid
FROM Suppliers S2, Catalog C2, Parts P2
WHERE S2.sid = C2.sid AND C2.pid = P2.pid
AND P2.color = 'Green';

--5.2.10
Select S.sname, Temp1.numParts
FROM Suppliers S,
 (Select Count(C1.pid) numParts, C1.sid
  FROM Catalog C1
  GROUP BY C1.sid) Temp1
  --,  () Temp2
WHERE S.sid = Temp1.sid
     AND S.sid NOT IN (
      Select Temp3.sid
      FROM (Select Distinct C.sid
             FROM Catalog C, Parts P
             WHERE C.pid = P.pid
             AND P.color <> 'Green') Temp3
     );
