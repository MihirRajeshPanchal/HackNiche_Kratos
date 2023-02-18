import streamlit as st

if st.button("Show Video"):
    from yoloVideo import yolo
    yolo()