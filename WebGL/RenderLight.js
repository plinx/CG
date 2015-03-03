function renderLight(canvas, scene, lights, camera) {
    if (!canvas || !canvas.getContext)
        return;

    var ctx = canvas.getContext("2d");
    if (!ctx.getImageData)
        return;

    var w = canvas.attributes.width.value;
    var h = canvas.attributes.height.value;
    ctx.fillStyle = "rgb(0,0,0)";
    ctx.fillRect(0, 0, w, h);

    var imgdata = ctx.getImageData(0, 0, w, h);
    var pixels = imgdata.data;

    scene.initialize();
    for (var k in lights)
        lights[k].initialize();
    camera.initialize();

    var i = 0;
    for (var y = 0; y < h; y++) {
        var sy = 1 - y / h;
        for (var x = 0; x < w; x++) {
            var sx = x / w;
            var ray = camera.generateRay(sx, sy);
            var result = scene.intersect(ray);
            if (result.geometry) {
                var color = Color.black;
                for (var k in lights) {
                    var lightSample = lights[k].sample(scene, result.position);

                    if (lightSample != lightSample.zero) {
                        var NdotL = result.normal.dot(lightSample.L);

                        // 夾角小約90度，即光源在平面的前面
                        if (NdotL >= 0)
                            color = color.add(lightSample.EL.multiply(NdotL));
                    }
                }
                pixels[i] = color.r * 255;
                pixels[i + 1] = color.g * 255;
                pixels[i + 2] = color.b * 255;
                pixels[i + 3] = 255;
            }
            i += 4;
        }
    }

    ctx.putImageData(imgdata, 0, 0);
}
