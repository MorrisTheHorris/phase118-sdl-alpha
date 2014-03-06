std::string getBuildingName( int layer, int index )
{
    switch(layer)
    {
    case 0:
        switch(index)
        {
        case 0:
            return "Grass";
        case 1:
            return "Dirt";
        case 2:
            return "Sea";
        case 3:
            return "Sand";
        }
    case 2:
        switch(index)
        {
        case 1:
            return "Solid Storage";
        case 2:
            return "Fluid Storage";
        case 3:
            return "Gas Storage";
        case 4:
            return "Radio Storage";
        case 5:
            return "Solid Collector";
        case 6:
            return "Fluid Collector";
        case 9:
            return "Gas Collector";
        }
    default:
        return "No Building";
    }
}

int getBuildingCost( int resource, int layer, int index )
{
    return build[index][0][resource];
}

bool isFunctional( int x, int y)
{
    if( world[2][x][y][0][1] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isBuilding( int x, int y)
{
    if( world[2][x][y][0][0] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
