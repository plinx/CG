Color = function(r, g, b) { this.r = r; this.g = g; this.b = b };

Color.prototype = {
    copy : function() { return new Color(this.r, this.g, this.b); },
    add : function(c) { return new Color(this.r + c.r, this.g + c.g, this.b + c.b); },
    multiply : function(s) { return new Color(this.r * s, this.g * s, this.b * s); },
    modulate : function(c) { return new Color(this.r * c.r, this.g * c.g, this.b * c.b); },
    saturate : function() { this.r = Math.min(this.r, 1); this.g = Math.min(this.g, 1); this.b = Math.min(this.b, 1); }
};

Color.black = new Color(0, 0, 0);
Color.white = new Color(1, 1, 1);
Color.red = new Color(1, 0, 0);
Color.green = new Color(0, 1, 0);
Color.blue = new Color(0, 0, 1);
