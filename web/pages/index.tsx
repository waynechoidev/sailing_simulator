import type { NextPage } from "next";
import Head from "next/head";
import Image from "next/image";
import { useEffect } from "react";
import styles from "../styles/Home.module.css";
import Script from "next/script";

const Home: NextPage = () => {
  useEffect(() => {
    const canvas = document.getElementById("canvas");

    // @ts-ignore
    window.Module = {
      preRun: [],
      postRun: [],
      canvas: canvas,
      print: console.log,
      printErr: console.error,
    };
  }, []);

  return (
    <>
      <canvas id="canvas" />
      <Script src="sailing_simulator.js" />
    </>
  );
};

export default Home;
