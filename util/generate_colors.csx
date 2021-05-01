// dotnet script generate_colors.csx

int ConvertRGB(int R, int G, int B)
{
	return (((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3));
}

var sceneColours = new List<(int r,int g ,int b, string name)>{
    (100, 130, 255, "scene 1"),
    (90, 120, 255, "scene 1"),
    (80, 110, 255, "scene 1"),
    (70, 100, 255, "scene 1"),
    (60, 90, 255, "scene 1"),
    (50, 80, 255, "scene 1"),
    (40, 70, 255, "scene 1"),
    (30, 60, 255, "scene 1"),
    (20, 50, 255, "scene 1"),
    (128, 255, 132, "preset -"),
    (128, 255, 132, "preset +"),
    (255,0,177, "scene selected"),
    (0,177,255, "scene bg"),
    (177,255,0, "scene bg"),
};

var hexes = new List<(string hex, string name)>{
    ("0a65fa", "primary selected"),
    ("ffff5f", "title (yellow)"),
    ("34e3f4", "alt text (cyan)"),
    ("819fe5", "menu selected"),
};

foreach (var c in sceneColours) {
    Console.WriteLine($"{c.name}: {ConvertRGB(c.r, c.g, c.b).ToString("X")}");
}

foreach (var c in hexes) {
    var r = int.Parse(c.hex.Substring(0, 2), System.Globalization.NumberStyles.AllowHexSpecifier);
    var g = int.Parse(c.hex.Substring(2, 2), System.Globalization.NumberStyles.AllowHexSpecifier);
    var b = int.Parse(c.hex.Substring(4, 2), System.Globalization.NumberStyles.AllowHexSpecifier);
    Console.WriteLine($"{c.name}: {ConvertRGB(r, g, b).ToString("X")}");
}