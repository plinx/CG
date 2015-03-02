Vector3 = function(x, y, z) { this.x = x; this.y = y; this.z = z; };

Vector3.prototype = {
    copy : function() { return new Vector3(this.x, this.y, this.z); },
    length : function() { return Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z); },
    sqrLength : function() { return this.x * this.x + this.y * this.y + this.z * this.z; },
    normalize : function() { var inv = 1/this.length(); return new Vector3(this.x * inv, this.y * inv, this.z * inv); },
    negate : function() { return new Vector3(-this.x, -this.y, -this.z); },
    add : function(v) { return new Vector3(this.x + v.x, this.y + v.y, this.z + v.z); },
    subtract : function(v) { return new Vector3(this.x - v.x, this.y - v.y, this.z - v.z); },
    multiply : function(f) { return new Vector3(this.x * f, this.y * f, this.z * f); },
    divide : function(f) { var invf = 1/f; return new Vector3(this.x * invf, this.y * invf, this.z * invf); },
    dot : function(v) { return this.x * v.x + this.y * v.y + this.z * v.z; },
    cross : function(v) { return new Vector3(-this.z * v.y + this.y * v.z, this.z * v.x - this.x * v.z, -this.y * v.x + this.x * v.y); }
};

Vector3.zero = new Vector3(0, 0, 0);


Ray3 = function(origin, direction) { this.origin = origin; this.direction = direction; }

Ray3.prototype = {
    getPoint : function(t) { return this.origin.add(this.direction.multiply(t)); }
};


Sphere = function(center, radius) { this.center = center; this.radius = radius; };

Sphere.prototype = {
    copy : function() { return new Sphere(this.center.copy(), this.radius.copy()); },

    initialize : function() {
        this.sqrRadius = this.radius * this.radius;
    },

    intersect : function(ray) {
        var v = ray.origin.subtract(this.center);
        var a0 = v.sqrLength() - this.sqrRadius;
        var DdotV = ray.direction.dot(v);

        if (DdotV <= 0) {
            var discr = DdotV * DdotV - a0;
            if (discr >= 0) {
                var result = new IntersectResult();
                result.geometry = this;
                result.distance = -DdotV - Math.sqrt(discr);
                result.position = ray.getPoint(result.distance);
                result.normal = result.position.subtract(this.center).normalize();
                return result;
            }
        }

        return IntersectResult.noHit;
    }
};

IntersectResult = function() {
    this.geometry = null;
    this.distance = 0;
    this.position = Vector3.zero;
    this.normal = Vector3.zero;
};

IntersectResult.noHit = new IntersectResult();

PerspectiveCamera = function(eye, front, up, fov) { this.eye = eye; this.front = front; this.refUp = up; this.fov = fov; };

PerspectiveCamera.prototype = {
    initialize : function() {
        this.right = this.front.cross(this.refUp);
        this.up = this.right.cross(this.front);
        this.fovScale = Math.tan(this.fov * 0.5 * Math.PI / 180) * 2;
    },

    generateRay : function(x, y) {
        var r = this.right.multiply((x - 0.5) * this.fovScale);
        var u = this.up.multiply((y - 0.5) * this.fovScale);
        return new Ray3(this.eye, this.front.add(r).add(u).normalize());
    }
};

function renderDepth(canvas, scene, camera, maxDepth) {
	var ctx = canvas.getContext("2d");
	var w = canvas.attributes.width.value;
	var h = canvas.attributes.height.value;
	ctx.fillStyle = "rgb(0,0,0)";
	ctx.fillRect(0, 0, w, h);
	var imgdata = ctx.getImageData(0, 0, w, h);
	var pixels = imgdata.data;
 
    scene.initialize();
    camera.initialize();
 
    var i = 0;
    for (var y = 0; y < h; y++) {
        var sy = 1 - y / h;
        for (var x = 0; x < w; x++) {
            var sx = x / w;            
            var ray = camera.generateRay(sx, sy);
            var result = scene.intersect(ray);
            if (result.geometry) {
                var depth = 255 - Math.min((result.distance / maxDepth) * 255, 255);
                pixels[i    ] = depth;
                pixels[i + 1] = depth;
                pixels[i + 2] = depth;
                pixels[i + 3] = 255;
            }
            i += 4;
        }
    }
 
    ctx.putImageData(imgdata, 0, 0);
}

function main()
{
	renderDepth(
		document.getElementById('cbox'),
		new Sphere(new Vector3(0, 10, -10), 10),
		new PerspectiveCamera(new Vector3(0, 10, 10), new Vector3(0, 0, -1), new Vector3(0, 1, 0), 90),
		20);
}

