 private void RunScript(List<Mesh> geo, DataTree<Mesh> notConnectRules, int x, int y, int dx, int dy, ref object A)
  {
    List<Mesh> output = new List<Mesh>(); // output
    
    List<List<Mesh>> notConnects = notConnectRules.Branches;
    List<List<int>> rules = createRules(geo, (List<List<Mesh>>) notConnects);
    List<Int32>[,] possibilityMap = buildMap(geo.Count, x, y);

    
    int setGrids = 0;


    while(setGrids != x * y){
       observation();
    }
    
    A = output;

  }




List<List<int>> createRules(List<Mesh> geo, List<List<Mesh>> notConnects){ // create rules for selection
    List<List<int>> rules = new List<List<int>>();

    Dictionary<Mesh, int> geoMap = new Dictionary<Mesh, int>();
    for(int i = 0; i < geo.Count; i++){ // create map to get index
        geoMap.Add(geo[i], i);
    }

    List<int> rules = new List<int>();

    for(int i = 0; i < notConnect.Count; i++){  // foreach geo mesh
        List<Mesh> objectOfNotConnect = notConnect[i];
        List<int> indexOfNotConnect = new List<>()  
        for(int j = 0; j < objectOfConnect.Count; j++){
            indexOfNotConnect.Add(geoMap[objectOfNotConnect[j]]);   // add index to the list
        }
        rules.Add(indexOfNotConnect);
    }
    return rules;
}

List<Int32>[,] buildMap(int size, int x, int y){ //  build a posibility map for grids
    HashSet<int>[,] map = new int[x, y];
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            List set = new List();
            for(int k = 0; k < size; k++){  // add all possible choice into the set
                set.Add(k);
            }
            map[i, j] = set;
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

void observation(){ // select a random grid and set it
    Random rd = new Random();
    int rx = rd.Next(0, x);
    int ry = rd.Next(0, y);

    while(setGrids != x * y || map[rx, ry].Count == 0){ // skip grids that already set
       rx = rd.Next(0, x);
       ry = rd.Next(0, y);
    }
    setGrid(rx, ry, chooseGrid(rx, ry));
    setGrids++;
}

Mesh chooseGrid(int x, int y){  // choose one possible random grid
    Random rd = new Random();
    int rdm = rd.Next(0, map[x, y].Count);
    return geo[possibilityMap[rdm]];    // select one random grid from possible geos

}

void setGrid(int x, int y, int type){  // add new grid to output
    Mesh ms = new Mesh();
    ms.CopyFrom(geo[type]);
    Vector3d oToP = new Vector3d(grid.Vertices[0]); //Point3f
    Vector3d oToN = new Vector3d(x * dx, y * dy, 0);
    ms.Translate(-oToP);
    ms.Translate(oToN);
    output.Add(ms);
}

void propagation(int originalType, int x, int y){
    if(x < 0 || x >= possibilityMap.Count || y < 0 || y >= possibilityMap[0].Count) return;
    List<int> possibility = possibilityMap[x, y];
    if(possibility == 0) return;    // skip if already set
    Set<int> rule = rules[originalType];

    int i = 0;
    while(i != possibility.Count){  // remove all impossible grids
        if(rule.Contains[possibility[i]]]){
            possibility.RemoveAt(i);
        }
        else{
            i++;
        }
    }

    if(possibility.Count == 1){ // if only one possibility left
        int type = possibility[0];
        setGrid(x, y, type);
        possibility.RemoveAt(0);

        propagation(type, x + 1, y);
        propagation(type, x - 1, y);
        propagation(type, x, y + 1);
        propagation(type, x, y - 1);
    }

    if(possibility.Count == 0) return;
}

bool selectRandomType(ref int type){
    Random rd = new Random();
    HashSet<int> choices = new HashSet<int>();
    for(int i = 0; i < possibility.Count; i++){ // create set for selectable items
        if(!rules[type].Contains(possibility[i])){
            choices.Add(possibility[i]);
        }
    }
    if(possibility.Count == 0) return false;
    int rdm = rd.Next(0, choices);
    int nType = choices[rdm];
    possibility.Remove(nType);
    type = nType;
    return true;
}















