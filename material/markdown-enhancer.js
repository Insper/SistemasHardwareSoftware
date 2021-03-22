{
    fetch(window.site_url + "config.yml").then((resp) => {
        return resp.text();
    }).then((text) => {
        let obj = jsyaml.load(text);
        obj.extensions.forEach((ext) => {
            let scr = document.createElement("script");
            scr.type = "text/javascript";
            scr.src = window.site_url + ext + ".js";

            document.body.appendChild(scr);
        });
    });
    
}