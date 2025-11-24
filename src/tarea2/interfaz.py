# -*- coding: utf-8 -*-

from __future__ import annotations

import sys
from rich import box
from rich.align import Align
from rich.console import Console
from rich.panel import Panel
from rich.prompt import Prompt

console = Console()


def panel_contenido(
    texto: str, *, titulo: str = "Proyecto 2", width: int | None = None
) -> None:
    """Imprime un Panel con doble línea y fondo azul."""
    console.clear()
    if width is None:
        width = min(90, max(40, console.size.width - 4))
    panel = Panel(
        Align.left(texto),
        title=titulo,
        title_align="center",
        padding=(1, 4),
        box=box.DOUBLE,
        width=width,
        style="white on blue",
    )
    console.print(panel, justify="left")


def pausa(msg: str = "Pulse [bold]Enter[/] para continuar…") -> None:
    Prompt.ask(msg, default="", show_default=False)


def leer_hilera(pregunta: str) -> str:
    s = Prompt.ask(pregunta).strip()
    return s


def leer_entero(pregunta: str, minimo: int | None = None, maximo: int | None = None) -> int:
    while True:
        try:
            s = Prompt.ask(pregunta)
            n = int(s)
            if minimo is not None and n < minimo:
                console.print(f"[red]El valor debe ser >= {minimo}[/]")
                continue
            if maximo is not None and n > maximo:
                console.print(f"[red]El valor debe ser <= {maximo}[/]")
                continue
            return n
        except ValueError:
            console.print("[red]Entrada inválida. Debe ser un número entero.[/]")


def leer_tecla(validos: str) -> str:
    """Lee una sola tecla válida sin requerir Enter."""
    try:
        import msvcrt  # type: ignore
    except Exception:
        msvcrt = None  # type: ignore

    if msvcrt is not None:  # Windows
        while True:
            ch = msvcrt.getwch()
            if ch in ("\x00", "\xe0"):
                _ = msvcrt.getwch()
                continue
            if ch in validos:
                console.print(ch, end="")
                return ch
    else:  # Unix
        import termios
        import tty

        fd = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            while True:
                ch = sys.stdin.read(1)
                if ch in validos:
                    console.print(ch, end="")
                    return ch
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)
