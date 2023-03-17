  void observation(int x, int y, int dx, int dy, ref int setGrids, ref List<Int32>[,] map, List<HashSet<Int32>> rules, List<Mesh> geo, ref List<Mesh> output){ // select a random grid and set it
    Random rd = new Random();
    Queue<Int32> q = new Queue<Int32>();
    q.Enqueue(rd.Next(0, x*y));

    while(!q.isEmpty()){
        int pos = q.Dequeue();
        rx = pos / y;
        ry = pos % y;
        if(rx < 0 || rx >= dx || ry < 0 || ry >= dy) return;
        if(map[rx, ry].Count == 0) return;

        int possibility = map[nxy,ny];
        int type = possibility[rd.Next(0, possibility.Count)];
        setGrid(rx, ry, dx, dy, type, geo, ref output);
        map[rx, ry].Clear();
    
        q.Enqueue((rx + 1) * y + ry);
        q.Enqueue((rx - 1) * y + ry);
        q.Enqueue(rx * y + ry + 1);
        q.Enqueue(rx * y + ry - 1);

    }
  }

  List<Int32>[,] buildMap(int size, int x, int y){ //  build a posibility map for grids
    List<Int32>[,] map = new List<Int32>[x, y];
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
        List<Int32> possibility = new List<Int32>();
        for(int k = 0; k < size; k++){  // add all possible choice into the set
          possibility.Add(k);
        }
        map[i, j] = possibility;
      }
    }
    return map;
  }

  List<Rectangle3d> createGrids(int x, int y, int dx, int dy){  // create base grids
    List<Rectangle3d> ret = new List<Rectangle3d>();
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
        Rectangle3d rect = new Rectangle3d(new Plane(new Point3d(i * dx, j * dy, 0), new Vector3d(0, 0, 1)), dx, dy);
        ret.Add(rect);
      }
    }
    return ret;
  }

  void setGrid(int x, int y, int dx, int dy, int type, List<Mesh> geo, ref List<Mesh> output){  // add new grid to output
    Mesh ms = new Mesh();
    ms.CopyFrom(geo[type]);
    Vector3d oToP = new Vector3d(geo[type].Vertices[0]); //Point3f
    Vector3d oToN = new Vector3d(x * dx, y * dy, 0);
    ms.Translate(-oToP);
    ms.Translate(oToN);
    output.Add(ms);
  }

  List<HashSet<Int32>> createRules(List<Mesh> geo, List<List<Mesh>> notConnects){ // create rules for selection
    List < HashSet<Int32>> rules = new List<HashSet<Int32>>();
    /*
    Dictionary<Mesh, Int32> geoMap = new Dictionary<Mesh, Int32>();
    for(int i = 0; i < geo.Count; i++){ // create map to get index
      geoMap.Add(geo[i], i);
    }

    for(int i = 0; i < notConnects.Count; i++){  // foreach geo mesh
      List<Mesh> objectOfNotConnect = notConnects[i];
      HashSet<Int32> indexOfNotConnect = new HashSet<Int32>();
      for(int j = 0; j < objectOfNotConnect.Count; j++){
        indexOfNotConnect.Add(geoMap[objectOfNotConnect[j]]);   // add index to the list
      }
      rules.Add(indexOfNotConnect);
    }*/
  
    HashSet<Int32> rule0 = new HashSet<Int32>();
    HashSet<Int32> rule1 = new HashSet<Int32>();
    HashSet<Int32> rule2 = new HashSet<Int32>();
    HashSet<Int32> rule3 = new HashSet<Int32>();
    
    rule0.Add(2);
    rule0.Add(3);
    rule0.Add(0);
    rule1.Add(0);
    
    rule1.Add(3);
    rule2.Add(0);
    rule2.Add(1);
    
    rule3.Add(0);
    rule3.Add(1);
    //rule3.Add(2);
    rules.Add(rule0);
    rules.Add(rule1);
    rules.Add(rule2);
    rules.Add(rule3);
    return rules;
  }
  void propagation(ref bool[,] visited, int originalType, int x, int y, int dx, int dy, ref List<int>[,] possibilityMap, List<HashSet<int>> rules, List<Mesh> geo, List<Mesh> output){
    if(x < 0 || x >= dx || y < 0 || y >= dy) return;
    if(visited[x, y]) return;
    visited[x, y] = true;
    List<int> possibility = possibilityMap[x, y];
    if(possibility.Count == 0) return;    // skip if already set
    HashSet<Int32> rule = rules[originalType];
    Random rd = new Random();
    for(int i = possibility.Count - 1; i >= 0; i--){
      if(rule.Contains(possibility[i])){
        possibility.RemoveAt(i);
      }
    }
    possibilityMap[x, y] = possibility;
    //if(possibility.Count == 1){ // if only one possibility left
      int type = possibility[rd.Next(0, possibility.Count)];
      setGrid(x, y, dx, dy, type, geo, ref output);
    possibility.Clear();

      propagation(ref visited, type, x + 1, y, dx, dy, ref possibilityMap, rules, geo, output);
      propagation(ref visited, type, x - 1, y, dx, dy, ref possibilityMap, rules, geo, output);
      propagation(ref visited, type, x, y + 1, dx, dy, ref possibilityMap, rules, geo, output);
      propagation(ref visited, type, x, y - 1, dx, dy, ref possibilityMap, rules, geo, output);
    //}

    if(possibility.Count == 0) return;
  }
