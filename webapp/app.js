var express = require("express");
var Busboy = require("busboy");
var fs = require("fs");
var exec = require("child_process").exec;
var path = require("path");

var f2wav = process.env.HOME + "/Git/noodles-neurons/f2wav";
var wav2f = process.env.HOME + "/Git/noodles-neurons/wav2f";

var server = express();

var counter = 0;

server.use(express.static("public"));

//a busboy multipart parser stolen from another one of my projects
var parseMultipart = function (req, res, next) {
  var busboy = new Busboy({headers: req.headers});
  busboy.on("file", function(fieldname, file, filename, encoding, mimetype) {
    req.params.filename = filename;
    req.params.mimetype = mimetype;
    req.params.encoding = encoding;
    file.on("data", function(data) {
      if (req.params.data) {
        req.params.data = Buffer.concat([req.params.data, data]);
      }
      else {
        req.params.data = data;
      }
    });
  });
  busboy.on("finish", function() {
    next();
  });

  req.pipe(busboy);
  return;
}

server.post("/upload", parseMultipart, function (req, res, next) {
  var filename = "/tmp/" + counter.toString() + req.params.filename;
  //req.params.data should contain a buffer with the data
  fs.writeFile(filename, req.params.data, function (err) {
    if (err) throw err;
    exec(wav2f + " " + filename + " > " + "/tmp/" + counter.toString() + ".txt", function (err, stdout, stderr) {
      //todo add an exec to run the prog on that tmpfile, parse the output,
      //return the wav
      res.status(200).send(stdout).end();
      //res.status(200).sendFile("/tmp/" + counter.toString() + ".txt");
      counter++;
    });
  });

});

server.get("/upload", function (req, res) {
  res.status(200)
     .sendFile(path.join(__dirname, "upload.html"));
});

server.listen(3031, function () {
  console.log("server listening at port 3031");
});
